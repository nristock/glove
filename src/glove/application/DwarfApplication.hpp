#pragma once

#include <memory>
#include <list>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
class World;
class ApplicationViewport;
using ApplicationViewportHandle = std::shared_ptr<ApplicationViewport>;

/**
* ApplicationFacets represent different aspects of an application.
*
* They can be used to initialize engine subsystems or configure other facets.
*
* Every facet has 4 lifecycle phases.
* <ul>
*     <li>Configure</li>
*     <li>Bootstrap</li>
*     <li>Initialize</li>
*     <li>Finalize</li>
* </ul>
*/
class BD_API_EXPORT ApplicationFacet {
  public:
    using Handle = std::shared_ptr<ApplicationFacet>;

    ApplicationFacet() : name("ApplicationFacet{Unnamed}") {}
    ApplicationFacet(std::string name) : name(std::move(name)) {}
    virtual ~ApplicationFacet() = default;

    virtual void Configure() {}
    virtual void Bootstrap() {}
    virtual void Initialize() {}
    virtual void Finalize() {}

    std::string ToString() { return name; }

  private:
    std::string name;
};

/**
* A DwarfApplication manages an application's lifecycle.
*
* ApplicationFacets can be attached when the application is constructed. Attached facets will be configured,
* bootstrapped, initialized and finalized in the order in which they were attached.
*/
class BD_API_EXPORT DwarfApplication {
  public:
    DwarfApplication();
    virtual ~DwarfApplication();

    /**
    * Main application entry point.
    *
    * Run configures, bootstraps and initializes all application facets. It then starts the application's RunLoop and
    * finalizes all application facets once the RunLoop exits.
    */
    virtual void Run();

    /// Adds an ApplicationFacet to the application.
    virtual void AddFacet(ApplicationFacet::Handle facet);

  protected:
    /// Configures application facets.
    virtual void Configure();

    /// Bootstraps application facets.
    virtual void Bootstrap();

    /// Initializes application facets.
    virtual void Initialize();

    virtual void RunLoop();

    /// Finalizes application facets.
    virtual void Finalize();

    std::list<ApplicationFacet::Handle> facets;
};
} // namespace BlueDwarf
