#include "glove/log/Logger.hpp"
#include "glove/log/MessageProcessor.hpp"

namespace {
using namespace glove;

MessageProcessor::Handle g_defaultLogPipeline;
}

namespace glove {
Logger::Logger(const std::string& name) : name(name) {
    messageProcessor = g_defaultLogPipeline;
}

void Logger::SetDefaultMessageProcessor(MessageProcessor::Handle processor) {
    g_defaultLogPipeline = processor;
}

void Logger::Log(const Message& msg) {
    msg.SetSource(name);
    messageProcessor->Process(msg);
}
}