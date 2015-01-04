#pragma once

#include <functional>
#include <typeinfo>

namespace glove {

typedef std::reference_wrapper<const std::type_info> TypeInfoRef;

struct TypeInfoComparator {
bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) {
    return lhs.get().hash_code() < rhs.get().hash_code();
}
};

}