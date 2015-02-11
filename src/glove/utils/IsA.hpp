#pragma once

#include "glove/GloveApi.hpp"

namespace glove {

template<typename T>
struct GLOVE_API_EXPORT IsA {
    template<typename O>
    IsA(const O* objectToCheck) {
        T* ptr = dynamic_cast<T*>(objectToCheck);
        value = ptr != nullptr;
    }

    template<typename O>
    IsA(const std::shared_ptr<O>& objectToCheck) {
        T* ptr = dynamic_cast<T*>(objectToCheck.get());
        value = ptr != nullptr;
    }

    operator bool() const {
        return value;
    }

    bool value;
};

}