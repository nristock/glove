#pragma once

#include <memory>

#include "glove/GloveApi.hpp"

namespace glove {
struct Message;

class GLOVE_API_EXPORT MessageProcessor {
  public:
    using Handle = std::shared_ptr<MessageProcessor>;

    virtual ~MessageProcessor() = default;

    virtual void Process(const Message& message) = 0;
};
}