#include "ks_logger.h"
#include "ks_framework.h"

namespace kronos {

    KS_SINGLETON_INSTANCE(Logger);

    Logger::Logger()
        : ComponentQueued("CQ_LOGGER"), m_File(KS_LOGGING_FILE_PATH),
        m_Bus(Framework::CreateBus<BusAsync>("BA_CQ_LOGGER", ks_event_log_message)){
        m_Bus->AddReceivingComponent(this);
    };

    KsCmdResult Logger::ProcessEvent(const EventMessage& eventMessage) {
        switch(eventMessage.eventCode) {
            case ks_event_log_message:
                ProcessMessage(eventMessage.Cast<LogEventMessage>());
                break;
        }
        return KS_CMDRESULT_NORETURN;
    }

    float Logger::ConvertTimestamp(uint32_t timestamp) {
        return (static_cast<float>(timestamp) / 1000.0f);
    }

    String Logger::ConvertSeverity(KsLogSeverity severity) {
        switch (severity) {
            case ks_log_debug:
                return KS_TERM_DEBUG
                "[DEBUG]"
                KS_TERM_RESET;
            case ks_log_info:
                return KS_TERM_INFO
                "[INFO]"
                KS_TERM_RESET;
            case ks_log_warn:
                return KS_TERM_WARN
                "[WARNING]"
                KS_TERM_RESET;
            case ks_log_error:
                return KS_TERM_ERROR
                "[ERROR]"
                KS_TERM_RESET;
            default:
                return "";
        }
    }

    void Logger::ProcessMessage(const LogEventMessage& eventMessage) {
        printf("%s", eventMessage.message.c_str());

        if (eventMessage.severity > ks_log_debug)
            m_File.Write(eventMessage.message.c_str(), eventMessage.message.size());
    }

}