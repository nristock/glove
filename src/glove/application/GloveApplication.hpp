#pragma once

#include <memory>
#include <list>

#include "glove/GloveApi.hpp"

namespace glove {
class World;
class ApplicationViewport;
using ApplicationViewportHandle = std::shared_ptr<ApplicationViewport>;

/**
* ApplicationFacets represent different aspects of an application.
*
* They can be used to initialize engine subsystems or configure other facets.
*
* Every facets has 4 lifecycle phases.
* <ul>
*     <li>Configure</li>
* </ul>
*/
class GLOVE_API_EXPORT ApplicationFacet {
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
* A GloveApplication manages an application's lifecycle.
*
* ApplicationFacets can be attached when the application is constructed. Attached facets will be configured,
* bootstrapped, initialized and finalized in the order in which they were attached.
*/
class GLOVE_API_EXPORT GloveApplication {
  public:
    GloveApplication();
    virtual ~GloveApplication();

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
} // namespace glove
