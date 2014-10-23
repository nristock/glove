#include "GloveObject.h"

#include "core/GloveCore.h"

namespace glove {

GloveObject::GloveObject() : GloveObject(true) {
}

GloveObject::GloveObject(bool queryGloveCore) : EnableProfilable() {
    if (queryGloveCore) {
        gloveCore = GloveCore::Instance();
    }
}

GloveObject::~GloveObject() {
}

} /* namespace glove */
