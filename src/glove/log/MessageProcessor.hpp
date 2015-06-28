#pragma once

#include <memory>

#include "glove/GloveApi.hpp"

namespace BlueDwarf {
struct Message;

/**
* A MessageProcessor is the generic interface for everything that either transforms, forwards or consumes a log message.
*
* Examples:
*   AsyncProcessor (forwards message to another processor on another thread)
*   ConsoleOutProcessor (prints the message to stdout and consumes it)
*/
class GLOVE_API_EXPORT MessageProcessor {
  public:
    using Handle = std::shared_ptr<MessageProcessor>;

    virtual ~MessageProcessor() = default;

    virtual void Process(const Message& message) = 0;
};
}