#pragma once

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

class BD_API_EXPORT SharedLibrary {
  public:
    virtual ~SharedLibrary() = default;

    /// @brief Loads a named symbol from the library.
    ///
    /// @param symbolName [in] The name of the symbol to load.
    /// @return Returns a pointer to the loaded symbol or throws SymbolNotFound if the symbol could not be found in the
    /// DSO.
    virtual void* GetSymbol(const std::string& symbolName) = 0;
};

} /* namespace BlueDwarf */