#include "glove/rendering/shader/MaterialAttributeSemantic.hpp"

namespace glove {
std::ostream& operator<< (std::ostream& os, MaterialAttributeSemantic attributeSemantic) {
    switch (attributeSemantic) {
        case MaterialAttributeSemantic::MVP_MAT:
            os << "MVP_MAT (ModelViewProjection Matrix)";
            break;
    }

    return os;
}
}