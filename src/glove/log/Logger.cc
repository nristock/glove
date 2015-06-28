#include "glove/log/Logger.hpp"
#include "glove/log/MessageProcessor.hpp"
#include "glove/log/processors/ConsoleOutProcessor.hpp"
#include "glove/log/format.hpp"

namespace {
using namespace BlueDwarf;

MessageProcessor::Handle g_defaultLogPipeline;


/**
* Fallback message processor used when no processor has been assigned.
*
* Writes to stdout:
*   [FALLBACK_MP]: Message
*/
class FallbackMessageProcessor : public MessageProcessor {
  public:
    void Process(const Message& msg) {
        fmt::printf("[FALLBACK_MP]: %s \n", msg.GetText());
    }
};
}

namespace BlueDwarf {
Logger::Logger(const std::string& name) : name(name) {
    messageProcessor = g_defaultLogPipeline;
}

void Logger::SetDefaultMessageProcessor(MessageProcessor::Handle processor) {
    g_defaultLogPipeline = processor;
}

void Logger::Log(const Message& msg) {
    msg.SetSource(name);
    GetMessageProcessor().Process(msg);
}

MessageProcessor& Logger::GetMessageProcessor() {
    if(messageProcessor) {
        return *messageProcessor;
    }

    if(g_defaultLogPipeline) {
        messageProcessor = g_defaultLogPipeline;
        return GetMessageProcessor();
    }

    if(!fallbackMessageProcessor) {
        fallbackMessageProcessor = std::make_shared<FallbackMessageProcessor>();
    }

    return *fallbackMessageProcessor;
}

void Logger::SetMessageProcessor(std::shared_ptr<MessageProcessor> messageProcessor) {
    this->messageProcessor = std::move(messageProcessor);

    if(fallbackMessageProcessor) {
        fallbackMessageProcessor.reset();
    }
}
}

