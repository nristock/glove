#pragma once

#include <memory>
#include <ctime>
#include <chrono>

#include "glove/GloveApi.hpp"
#include "glove/log/MessageProcessor.hpp"

namespace glove {
struct Message;

class GLOVE_API_EXPORT DefaultFormatterProcessor : public MessageProcessor {
  public:
    DefaultFormatterProcessor(MessageProcessor::Handle nextProcessor) : nextProcessor(std::move(nextProcessor)) {}

    virtual void Process(const Message& message) {
        std::stringstream messageText;

        using std::chrono::duration_cast;

        auto messageTimeSinceEpoch = message.GetTimestamp().time_since_epoch();
        auto hours = duration_cast<std::chrono::hours>(messageTimeSinceEpoch);
        messageTimeSinceEpoch -= hours;

        auto minutes = duration_cast<std::chrono::minutes>(messageTimeSinceEpoch);
        messageTimeSinceEpoch -= minutes;

        auto seconds = duration_cast<std::chrono::seconds>(messageTimeSinceEpoch);
        messageTimeSinceEpoch -= seconds;

        auto millis = duration_cast<std::chrono::milliseconds>(messageTimeSinceEpoch);

        auto nowCTime = std::chrono::high_resolution_clock::to_time_t(message.GetTimestamp());
        auto nowLocalCTime = std::localtime(&nowCTime);

        messageText << "[" << 1900 + nowLocalCTime->tm_year << "-" << nowLocalCTime->tm_mon + 1 << "-" << nowLocalCTime->tm_mday << " "
                << nowLocalCTime->tm_hour << ":" << minutes.count() << ":" << seconds.count() << "." << millis.count()
                << " {" << message.GetThreadId() << "}] ["
                    << message.GetLogLevel() << "]";

        if(!message.GetProperty("__FUNCTION__").empty()) {
            messageText << " [" << message.GetProperty("__FUNCTION__") << " @ " << message.GetProperty("__FILE__") << ":" << message.GetProperty("__LINE__") << "]";
        }
        messageText << ": " << message.GetMessage();

        message.SetText(messageText.str());

        nextProcessor->Process(message);
    }

  private:
    MessageProcessor::Handle nextProcessor;
};
}