#include "ks_command_dispatcher.h"

namespace kronos {
    KsCmdResult CommandDispatcher::ProcessEvent(const EventMessage& message) {
        switch (message.eventCode) {
            case ks_event_comms_dispatch:
                auto commandMessage = message.Cast<CommandMessage>();
                m_CommandMessages[commandMessage.commandId](commandMessage.parameter);
                break;
        }
        return KS_CMDRESULT_NORETURN;
    }

    KsResultType CommandDispatcher::RegisterCommand(KsCommandId opcode, const std::function<void(void*)>& pFunction) {
        m_CommandMessages[opcode] = pFunction;
        return ks_success;
    }
}