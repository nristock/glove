#pragma once

#include <memory>

#include "glove/GloveApi.hpp"
#include "glove/log/Message.hpp"
#include "MessageProcessor.hpp"

#if defined(_MSC_VER)
#define __GLOVE_PRETTY_FUNC_ __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__) || defined(__PRETTY_FUNCTION__)
#define __GLOVE_PRETTY_FUNC_ __PRETTY_FUNCTION__
#else
#define __GLOVE_PRETTY_FUNC_ __func__
#endif

namespace glove {
#define M_TAG __FILE__, __GLOVE_PRETTY_FUNC_, __LINE__
#define LOG(_level, _args)                                                                                             \
    {                                                                                                                  \
        glove::Logger _anonymousLogger;                                                                                \
        _anonymousLogger._level(_args, M_TAG);                                                                         \
    }

#define L_INFO(_args) LOG(Info, _args)
#define L_WARNING(_args) LOG(Warning, _args)
#define L_ERROR(_args) LOG(Error, _args)
#define L_DEBUG(_args) LOG(Debug, _args)
#define L_TRACE(_args) LOG(Trace, _args)

class MessageProcessor;

/**
* Creates log messages and passes them to the assigned message processor.
*
* If no global default message processor (SetDefaultMessageProcessor) has been set, a fallback processor will be
* created. The fallback simply writes the log message's text and an indication that the fallback processor has been
* used.
*
* Named loggers set the source property of all messages logged by them.
*
* If file, function and line information was procided when creating a log message, a tagged message will be created. The
* tagged message has the three custom properties __FUNCTION__, __FILE__ and __LINE__ which can be used by a formatter.
*/
class GLOVE_API_EXPORT Logger {
  public:
    Logger() : Logger("") {}
    Logger(const std::string& name);

    /// Sets the global default message processor. Only effects newly created loggers.
    static void SetDefaultMessageProcessor(std::shared_ptr<MessageProcessor> processor);

    template <typename TMessageConstructorArg> void Error(TMessageConstructorArg&& arg) {
        Log(Message(LogLevel::Error, std::forward<TMessageConstructorArg>(arg)));
    }
    template <typename TMessageConstructorArg> void Warning(TMessageConstructorArg& arg) {
        Log(Message(LogLevel::Warning, std::forward<TMessageConstructorArg>(arg)));
    }
    template <typename TMessageConstructorArg> void Info(TMessageConstructorArg&& arg) {
        Log(Message(LogLevel::Info, std::forward<TMessageConstructorArg>(arg)));
    }
    template <typename TMessageConstructorArg> void Debug(TMessageConstructorArg&& arg) {
        Log(Message(LogLevel::Debug, std::forward<TMessageConstructorArg>(arg)));
    }
    template <typename TMessageConstructorArg> void Trace(TMessageConstructorArg&& arg) {
        Log(Message(LogLevel::Trace, std::forward<TMessageConstructorArg>(arg)));
    }

    template <typename TMessageConstructorArg>
    void Error(TMessageConstructorArg&& arg, const char* file, const char* function, int line) {
        Log(MakeTaggedMessage(LogLevel::Error, std::forward<TMessageConstructorArg>(arg), file, function, line));
    }
    template <typename TMessageConstructorArg>
    void Warning(TMessageConstructorArg&& arg, const char* file, const char* function, int line) {
        Log(MakeTaggedMessage(LogLevel::Warning, std::forward<TMessageConstructorArg>(arg), file, function, line));
    }
    template <typename TMessageConstructorArg>
    void Info(TMessageConstructorArg&& arg, const char* file, const char* function, int line) {
        Log(MakeTaggedMessage(LogLevel::Info, std::forward<TMessageConstructorArg>(arg), file, function, line));
    }
    template <typename TMessageConstructorArg>
    void Debug(TMessageConstructorArg&& arg, const char* file, const char* function, int line) {
        Log(MakeTaggedMessage(LogLevel::Debug, std::forward<TMessageConstructorArg>(arg), file, function, line));
    }
    template <typename TMessageConstructorArg>
    void Trace(TMessageConstructorArg&& arg, const char* file, const char* function, int line) {
        Log(MakeTaggedMessage(LogLevel::Trace, std::forward<TMessageConstructorArg>(arg), file, function, line));
    }

    template <typename TMessageConstructorArg>
    Message MakeTaggedMessage(LogLevel logLevel, TMessageConstructorArg&& arg, const char* file,
                              const char* function, int line) {
        Message message(logLevel, std::forward<TMessageConstructorArg>(arg));

        message.SetProperty("__FUNCTION__", function);
        message.SetProperty("__FILE__", file);
        message.SetProperty("__LINE__", std::to_string(line));

        return std::move(message);
    }

    void Log(const Message& msg);

    /// Sets the loggers message processor and releases the fallback processor if one had been created.
    void SetMessageProcessor(std::shared_ptr<MessageProcessor> messageProcessor);

  private:
    std::string name;
    std::shared_ptr<MessageProcessor> messageProcessor;
    std::shared_ptr<MessageProcessor> fallbackMessageProcessor;

    /// Returns the assigned message processor or creates and returns a fallback processor of no default has been set.
    MessageProcessor& GetMessageProcessor();
};
}