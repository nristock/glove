#pragma once

#include <list>
#include <memory>

#include <boost/uuid/uuid.hpp>

namespace glove {

typedef boost::uuids::uuid ExtensionUuid;

typedef boost::uuids::uuid SubsystemType;
typedef boost::uuids::uuid SubsystemUuid;

typedef std::list<SubsystemType> SubsystemTypeList;

class IExtensionSearcher;

class ISharedLibraryLoader;
class ISharedLibraryLoaderFactory;

class ISubsystem;
class ISubsystemDefinition;
class ISubsystemFactory;

class ISystemExtension;
class ISystemExtensionLoader;

class ISubsystemDefinitionRegistry;
class ISubsystemInstanceRegistry;

typedef std::shared_ptr<IExtensionSearcher> IExtensionSearcherPtr;
typedef std::shared_ptr<ISharedLibraryLoader> ISharedLibraryLoaderPtr;
typedef std::shared_ptr<ISharedLibraryLoaderFactory> ISharedLibraryLoaderFactoryPtr;
typedef std::shared_ptr<ISubsystemDefinition> ISubsystemDefinitionPtr;
typedef std::shared_ptr<ISubsystemFactory> ISubsystemFactoryPtr;
typedef std::shared_ptr<ISystemExtension> ISystemExtensionPtr;
typedef std::shared_ptr<ISubsystemDefinitionRegistry> ISubsystemDefinitionRegistryPtr;
typedef std::shared_ptr<ISubsystemInstanceRegistry> ISubsystemInstanceRegistryPtr;
typedef std::shared_ptr<ISubsystem> ISubsystemPtr;
typedef std::shared_ptr<ISystemExtensionLoader> ISystemExtensionLoaderHandle;

typedef std::list<ISubsystemDefinitionPtr> SubsystemDefinitionList;
typedef std::list<ISubsystemPtr> SubsystemInstanceList;

typedef ISystemExtensionPtr (*LoadSystemExtensionLibraryFunc)();
typedef void (*UnloadSystemExtensionLibraryFunc)();
} /* namespace glove */