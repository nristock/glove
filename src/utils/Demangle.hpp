#pragma once

namespace glove {

/*!
 * Demangles type names returned by typeid(...).name()
 * Windows doesn't seem to need demangling so the implementation simply returns the input on this platform.
 * On linux we use cxxabi's __cxa_demangle function.
 */
const char* Demangle(const char* mangledString);

} /* namespace glove */