#pragma once

#include <memory>

#include <boost/uuid/uuid.hpp>

namespace BlueDwarf {

template <class T> using Handle = std::shared_ptr<T>;

class ExtensionSearcher;
using ExtensionSearcherHandle = Handle<ExtensionSearcher>;

class ModuleLoader;
using ModuleLoaderHandle = Handle<ModuleLoader>;

class Module;
using ModuleHandle = Handle<Module>;
typedef std::unique_ptr<Module> (*ModuleCreateFunc)();

} /* namespace BlueDwarf */

#if !defined(BD_NATEX_FWD_ONLY)
#include "glove/natex/Module.hpp"
#include "glove/natex/ModuleLoader.hpp"
#include "glove/natex/SharedLibrary.hpp"
#include "glove/natex/SharedLibraryLoader.hpp"
#include "glove/natex/ExtensionSearcher.hpp"
#include "glove/natex/DirectoryExtensionSearcher.hpp"
#include "glove/natex/BifrostLoader.hpp"
#endif