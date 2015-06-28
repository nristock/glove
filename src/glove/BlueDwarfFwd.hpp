#pragma once

#include <memory>
#include "glove/BlueDwarfApi.hpp"

#define BD_MAKE_SHARED(type_) typedef std::shared_ptr<type_>
#define BD_FWD_DECL(type_)                                                                                          \
    class type_;                                                                                                       \
    BD_MAKE_SHARED(type_) type_##Pointer;                                                                           \
    BD_MAKE_SHARED(type_) type_##Ptr;
#define BD_FWD_DECL_STRUCT(type_)                                                                                   \
    struct type_;                                                                                                      \
    BD_MAKE_SHARED(type_) type_##Pointer;                                                                           \
    BD_MAKE_SHARED(type_) type_##Ptr;

namespace BlueDwarf {

BD_FWD_DECL(DwarfCore);
}
