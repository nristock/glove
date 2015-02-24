#pragma once

#include <memory>
#include "glove/GloveApi.hpp"

#define GLOVE_MAKE_SHARED(type_) typedef std::shared_ptr<type_>
#define GLOVE_FWD_DECL(type_)                                                                                          \
    class type_;                                                                                                       \
    GLOVE_MAKE_SHARED(type_) type_##Pointer;                                                                           \
    GLOVE_MAKE_SHARED(type_) type_##Ptr;
#define GLOVE_FWD_DECL_STRUCT(type_)                                                                                   \
    struct type_;                                                                                                      \
    GLOVE_MAKE_SHARED(type_) type_##Pointer;                                                                           \
    GLOVE_MAKE_SHARED(type_) type_##Ptr;

namespace glove {

GLOVE_FWD_DECL(GloveCore);
}
