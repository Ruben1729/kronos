#pragma once

#include "drivers/protocols/ks_io.h"
#include "ks_module.h"
#include "ks_component_active.h"

namespace kronos {
    class Bus;

    class HealthMonitor;

    //! \class Framework
    //! \brief A class that implements the framework using the Singleton design pattern
    class Framework {
        friend class HealthMonitor;

    KS_SINGLETON(Framework);

    public:
        //! \brief Constructor that creates the instance of the Framework Singleton
        Framework() = default;

        //! \brief Destructor that deletes the instance to the Framework Singleton
        ~Framework() = default;

    public:
        //! \brief Convenience method for static calls. See _AddModule().
        template<typename T, typename... Args>
        static inline ErrorOr<void> AddModule(Args&& ... args) {
            return s_Instance->_AddModule<T>(std::forward<Args>(args)...);
        }

        //! \brief Convenience method for static calls. See _CreateComponent().
        template<typename T, typename... Args>
        static inline ErrorOr<T*> CreateComponent(const String& name, Args&& ... args) {
            return s_Instance->_CreateComponent<T, Args...>(name, std::forward<Args>(args)...);
        }

        //! \brief Convenience method for static calls. See _CreateSingletonComponent().
        template<typename T>
        static inline ErrorOr<void> CreateSingletonComponent() {
            return s_Instance->_CreateSingletonComponent<T>();
        }

        //! \brief Convenience method for static calls. See _CreateBus().
        template<typename T=Bus, typename... Args>
        static inline ErrorOr<T*> CreateBus(const String& name, Args&& ... args) {
            return s_Instance->_CreateBus<T, Args...>(name, std::forward<Args>(args)...);
        }

        //! \brief Convenience method for static calls. See _CreateDriver().
        template<typename T, typename... Args>
        static inline ErrorOr<T*> CreateDriver(const String& name, Args&& ... args) {
            return s_Instance->_CreateDriver<T, Args...>(name, std::forward<Args>(args)...);
        }

        template<class T>
        static inline ErrorOr<EventMessage*> CreateEventMessage(T&& data, KsEventCodeType eventCode, Bus* returnBus = nullptr) {
            return s_Instance->_CreateEventMessage<T>(std::forward<T>(data), eventCode, returnBus);
        }

        template<class T>
        static inline ErrorOr<EventMessage*>
        CreateEventMessage(const T& data, KsEventCodeType eventCode, Bus* returnBus = nullptr) {
            return s_Instance->_CreateEventMessage<T>(data, eventCode, returnBus);
        }

        //! \brief Convenience method for static calls. See _HasModule().
        template<typename T>
        static inline bool HasModule() {
            return s_Instance->_HasModule<T>();
        }

    public:
        //! \brief Convenience method for static calls. See _Start().
        KS_SINGLETON_EXPOSE_METHOD(_Start, ErrorOr<void> Start());

        //! \brief Convenience method for static calls. See _InitModules().
        KS_SINGLETON_EXPOSE_METHOD(_InitModules, ErrorOr<void> InitModules());

        KS_SINGLETON_EXPOSE_METHOD(_GetBus, ErrorOr<Bus*> GetBus(const String& name), name);

        KS_SINGLETON_EXPOSE_METHOD(_GetDriver, ErrorOr<IoDriver*> GetDriver(const String& name), name);

        KS_SINGLETON_EXPOSE_METHOD(_CreateEventMessage,
                                   ErrorOr<EventMessage*>
                                       CreateEventMessage(KsEventCodeType eventCode, Bus * returnBus = nullptr),
                                   eventCode,
                                   returnBus);

        KS_SINGLETON_EXPOSE_METHOD(_DeleteEventMessage,
                                   ErrorOr<void> DeleteEventMessage(const EventMessage* eventMessage),
                                   eventMessage);

    private:
        //! \brief Initializes all the components and starts the FreeRTOS sched
        ErrorOr<void> _Start();

        //! \brief Initializes and adds a module to the framework.
        //!
        //! \tparam T The module class type.
        //! \tparam Args The types of the constructor arguments required to instantiate the module class.
        //! \param args The constructor arguments required to instantiate the module class.
        template<typename T, typename... Args>
        ErrorOr<void> _AddModule(Args&& ... args) {
            static_assert(std::is_base_of_v<IModule, T>, "T must extend IModule!");

            if (_HasModule<T>()) {
                // Module already added
                KS_THROW(ks_error_module_exists, void);
            }

            // Initializing Module
            auto id = ClassID<T>();
            auto ptr = new T(std::forward<Args>(args)...);
            m_Modules[id] = Scope<T>(ptr);

            return {};
        }

        //! \brief Creates a new component and registers it into the framework.
        //!
        //! \tparam T The component class type.
        //! \tparam Args The types of the constructor arguments required to instantiate the component class.
        //! \param name The name of the new component (must be different from existing components).
        //! \param args The constructor arguments required to instantiate the component class.
        //! \return The component that was created, nullptr if there was an error.
        template<class T, typename... Args>
        ErrorOr<T*> _CreateComponent(const std::string& name, Args&& ... args) {
            static_assert(std::is_base_of_v<ComponentBase, T>, "T must extend ComponentBase!");

            if (m_Components.contains(name)) {
                // Component already created
                KS_THROW(ks_error_component_exists, void);
            }

            auto ref = CreateRef<T>(name, std::forward<Args>(args)...);
            m_Components[name] = ref;

            if constexpr (std::is_base_of_v<ComponentActive, T>) {
                m_ActiveComponents.push_back(name);
            }

            return ref.get();
        }

        template<typename T>
        ErrorOr<void> _CreateSingletonComponent() {
            static_assert(std::is_base_of_v<ComponentBase, T>, "T must extend ComponentBase!");

            T::CreateInstance();
            auto ref = T::GetInstanceRef();
            const auto& name = ref->GetName();

            if (m_Components.contains(name)) {
                // Component already created
                KS_THROW(ks_error_component_exists, void);
            }

            m_Components[name] = ref;
            if constexpr (std::is_base_of_v<ComponentActive, T>) {
                m_ActiveComponents.push_back(name);
            }

            return {};
        }

        //! \brief Creates a new bus and registers it into the framework.
        //!
        //! \tparam T The bus class type.
        //! \tparam Args The types of the constructor arguments required to instantiate the bus class.
        //! \param name The name of the new component (must be different from existing busses).
        //! \param args The constructor arguments required to instantiate the bus class.
        //! \return The bus that was created, nullptr if there was an error.
        template<class T, typename... Args>
        ErrorOr<T*> _CreateBus(const std::string& name, Args&& ... args) {
            static_assert(std::is_base_of_v<Bus, T>, "T must extend Bus!");

            if (m_Busses.contains(name)) {
                // Bus already created
                KS_THROW(ks_error_bus_exists, T*);
            }

            auto ref = CreateRef<T>(name, std::forward<Args>(args)...);
            m_Busses[name] = ref;
            return ref.get();
        }

        template<class T, typename... Args>
        ErrorOr<T*> _CreateDriver(const String& name, Args&& ... args) {
            static_assert(std::is_base_of_v<IoDriver, T>, "T must extend IoDriver!");

            if (m_Drivers.contains(name)) {
                // Bus already created
                KS_THROW(ks_error_bus_exists, T*);
            }

            auto ref = CreateRef<T>(std::forward<Args>(args)...);
            m_Drivers[name] = ref;
            return ref.get();
        }

        template<class T>
        ErrorOr<EventMessage*> _CreateEventMessage(T&& data, KsEventCodeType eventCode, Bus* returnBus = nullptr) {
            Scope <EventMessage> eventMessage = std::make_unique<EventMessage>();
            eventMessage->eventCode = eventCode;
            eventMessage->data = std::make_any<T>(std::forward<T>(data));
            eventMessage->returnBus = returnBus;

            auto* eventMessagePtr = eventMessage.get();
            m_EventMessages.emplace(eventMessagePtr, std::forward<Scope < EventMessage>>
            (eventMessage));

            return eventMessagePtr;
        }

        template<class T>
        ErrorOr<EventMessage*> _CreateEventMessage(const T& data, KsEventCodeType eventCode, Bus* returnBus = nullptr) {
            Scope <EventMessage> eventMessage = std::make_unique<EventMessage>();
            eventMessage->eventCode = eventCode;
            eventMessage->data = std::make_any<T>(data);
            eventMessage->returnBus = returnBus;

            auto* eventMessagePtr = eventMessage.get();
            m_EventMessages.emplace(eventMessagePtr, std::forward<Scope < EventMessage>>
            (eventMessage));
            return eventMessagePtr;
        }

        ErrorOr<EventMessage*> _CreateEventMessage(KsEventCodeType eventCode, Bus* returnBus = nullptr);

        ErrorOr<void> _DeleteEventMessage(const EventMessage* eventMessage);

        //!
        //! \tparam T
        //! \return
        template<typename T>
        bool _HasModule() {
            return m_Modules.contains(ClassID<T>());
        }

        //! \brief
        //!
        //! \param moduleList
        //! \return
        ErrorOr<void> _InitModules();

        ErrorOr<Bus*> _GetBus(const String& name);

        ErrorOr<IoDriver*> _GetDriver(const String& name);

    private:
        List <KsIdType> m_ModuleList;
        Map <KsIdType, Scope<IModule>> m_Modules;
        Map <String, Ref<ComponentBase>> m_Components;
        List <String> m_ActiveComponents;
        Map <String, Ref<Bus>> m_Busses;
        Map <String, Ref<IoDriver>> m_Drivers;
        Map<const EventMessage*, Scope < EventMessage>> m_EventMessages;

    };

}
