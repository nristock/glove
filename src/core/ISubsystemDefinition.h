#pragma once

#include <set>

#include <core/GloveFwd.h>
#include <core/ISubsystemFactory.h>

#include <boost/uuid/uuid.hpp>

namespace glove {

typedef boost::uuids::uuid SystemType;
typedef boost::uuids::uuid SystemUuid;

typedef std::set<SystemType> SystemTypeList;

/// @brief Interface for subsystem definitions
class ISubsystemDefinition {
public:
    virtual ~ISubsystemDefinition() {};

    /// @brief Returns a human-readable name of the subsystem.
    virtual const std::string& GetSystemName() = 0;

    /// @brief Returns the subsyste's *unique* UUID.
    virtual const SystemUuid& GetSystemUuid() = 0;

    /// @brief Returns the subsystem's system type.
    virtual const SystemType& GetSystemType() = 0;

    /// @brief Returns a list of system types representing dependencies which will have to be loaded first.
    virtual const SystemTypeList& GetSystemDependencies() = 0;

    /// @brief Returns the subsystem's factory.
    virtual const ISubsystemFactoryPtr& GetSystemFactory() = 0;
};

} /* namespace glove */