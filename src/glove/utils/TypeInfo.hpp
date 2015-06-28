#pragma once

#include <functional>
#include <typeinfo>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

typedef std::reference_wrapper<const std::type_info> TypeInfoRef;

struct BD_API_EXPORT TypeInfoComparator {
bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) {
    return lhs.get().hash_code() < rhs.get().hash_code();
}
};

}