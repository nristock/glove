#pragma once

#include <memory>
#include <mutex>

#include "glove/BlueDwarfApi.hpp"
#include "glove/log/MessageProcessor.hpp"
#include "glove/threading/ThreadPool.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {
struct Message;

/**
* Queues incoming messages for processing on another thread.
*
* This processor should be the first in a non-blocking log pipeline. (Non-blocking from the log source point of view.)
*/
class BD_API_EXPORT AsyncProcessor : public MessageProcessor {
  public:
    AsyncProcessor(MessageProcessor::Handle nextProcessor) : processingPool(1), nextProcessor(nextProcessor) {}

    virtual void Process(const Message& message) {
        processingPool.SubmitWork(std::make_shared<ProcessMessageTask>(nextProcessor, message));
    }

  private:
    class ProcessMessageTask : public Task {
      public:
        ProcessMessageTask(MessageProcessor::Handle processor, Message message)
            : processor(std::move(processor)), message(std::move(message)) {}

        virtual void Execute() { processor->Process(message); }

      private:
        MessageProcessor::Handle processor;
        Message message;
    };

    ThreadPool processingPool;
    MessageProcessor::Handle nextProcessor;
};
}