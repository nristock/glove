#pragma once

#include <memory>
#include <mutex>

#include "glove/GloveApi.hpp"
#include "glove/log/MessageProcessor.hpp"

namespace glove {
struct Message;

class GLOVE_API_EXPORT ConsoleOutProcessor : public MessageProcessor {
  public:
    virtual void Process(const Message& message) {
        std::unique_lock<std::mutex> writeLock(writeMutex);
        std::cout << message.GetText() << std::endl;
    }

  private:
    std::mutex writeMutex;
};
}