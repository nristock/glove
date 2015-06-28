#pragma once

#include <memory>
#include <ctime>
#include <chrono>

#include "glove/BlueDwarfApi.hpp"
#include "glove/log/MessageProcessor.hpp"

namespace BlueDwarf {
struct Message;

/**
* The default message formatter create message text of the format:
*   Year-Month-Day Hour-Minute-Second.Milli [LEVEL] TID : Message
*   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  ^^^^^  ^^^   ^^^^^^
*   |- ISO8601 Date and Time                 |      |     |- Event message
*      YYYY-MM-DD hh:mm:ss.sss               |      |- Thread ID
*                                            |- 5-character Log level
*
*/
class BD_API_EXPORT DefaultFormatterProcessor : public MessageProcessor {
  public:
    DefaultFormatterProcessor(MessageProcessor::Handle nextProcessor) : nextProcessor(std::move(nextProcessor)) {}

    virtual void Process(const Message& message) {
        message.SetText(FormatMessage(message));
        nextProcessor->Process(message);
    }

  protected:
    virtual std::string FormatMessage(const Message& message) {
        return fmt::format("{0} [{1}] {2} : {3}", FormatTimestamp(message), message.GetLogLevel(),
                                    message.GetThreadId(), message.GetMessage());
    }

    virtual std::string FormatTimestamp(const Message& message) {
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

        return fmt::format("[{0}-{1}-{2} {3}:{4}:{5}.{6}]", 1900 + nowLocalCTime->tm_year, nowLocalCTime->tm_mon + 1,
                           nowLocalCTime->tm_mday, nowLocalCTime->tm_hour, minutes.count(), seconds.count(),
                           millis.count());
    }

  private:
    MessageProcessor::Handle nextProcessor;
};
}