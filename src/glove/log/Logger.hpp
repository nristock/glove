#pragma once

#include <memory>

#include "glove/GloveApi.hpp"
#include "glove/log/Message.hpp"

namespace glove {
class MessageProcessor;

class GLOVE_API_EXPORT Logger {
  public:
    Logger(const std::string& name);

    static void SetDefaultMessageProcessor(std::shared_ptr<MessageProcessor> processor);

    template <typename TMessageConstructorArg> void Error(const TMessageConstructorArg& arg) {
        Log(Message(LogLevel::Error, arg));
    }
    template <typename TMessageConstructorArg> void Warning(const TMessageConstructorArg& arg) {
        Log(Message(LogLevel::Warning, arg));
    }
    template <typename TMessageConstructorArg> void Info(const TMessageConstructorArg& arg) {
        Log(Message(LogLevel::Info, arg));
    }
    template <typename TMessageConstructorArg> void Debug(const TMessageConstructorArg& arg) {
        Log(Message(LogLevel::Debug, arg));
    }
    template <typename TMessageConstructorArg> void Trace(const TMessageConstructorArg& arg) {
        Log(Message(LogLevel::Trace, arg));
    }

    void Log(const Message& msg);

  private:
    std::string name;
    std::shared_ptr<MessageProcessor> messageProcessor;
};

namespace log_internal {
template <typename TMessageConstructorArg>
glove::Message CreateMessage(glove::LogLevel logLevel, TMessageConstructorArg arg, const char* function,
                             const char* file, int line) {
    auto message = glove::Message{logLevel, arg};

    message.SetProperty("__FUNCTION__", function);
    message.SetProperty("__FILE__", file);
    message.SetProperty("__LINE__", std::to_string(line));

    return std::move(message);
}
}
}

#define LOG(_logger, _level, _args)                                                                                    \
    { _logger.Log(glove::log_internal::CreateMessage(glove::LogLevel::_level, _args, __func__, __FILE__, __LINE__)); }