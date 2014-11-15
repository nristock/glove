#pragma once

#include <list>

#include <boost/uuid/uuid.hpp>

#include <core/GloveFwd.h>
#include <core/natex/ISubsystemFactory.h>

namespace glove {

typedef boost::uuids::uuid SubsystemType;
typedef boost::uuids::uuid SubsystemUuid;

typedef std::list<SubsystemType> SubsystemTypeList;

/// @brief Interface for subsystem definitions
class ISubsystemDefinition {
  public:
    virtual ~ISubsystemDefinition() {};

    /// @brief Returns a human-readable name of the subsystem.
    virtual const std::string& GetSystemName() = 0;

    /// @brief Returns the subsystem's *unique* UUID.
    virtual const SubsystemUuid& GetSystemUuid() = 0;

    /// @brief Returns the subsystem's system type.
    virtual const SubsystemType& GetSystemType() = 0;

    /// @brief Returns a list of system types representing dependencies which will have to be loaded first.
    virtual const SubsystemTypeList& GetSystemDependencies() = 0;

    /// @brief Returns the subsystem's factory.
    virtual const ISubsystemFactoryPtr& GetSystemFactory() = 0;
};

} /* namespace glove */