#include "glove/application/GloveApplication.hpp"
#include "glove/world/World.hpp"

namespace glove {

void GloveApplication::Run() {
    Configure();
    Bootstrap();
    Initialize();

    RunLoop();

    Finalize();
}

void GloveApplication::Configure() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Configure Facet: {0}", facet->ToString()))
        try {
            facet->Configure();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet configuration failed: {0}", ex.what()));
        }
    }
}

void GloveApplication::Bootstrap() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Bootstrapping Facet: {0}", facet->ToString()))
        try {
            facet->Bootstrap();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet bootstrap failed: {0}", ex.what()));
        }
    }
}

void GloveApplication::Initialize() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Initialize Facet: {0}", facet->ToString()))
        try {
            facet->Initialize();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet initialization failed: {0}", ex.what()));
        }
    }
}

void GloveApplication::RunLoop() {
}

void GloveApplication::Finalize() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Finalize Facet: {0}", facet->ToString()))
        try {
            facet->Finalize();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet finalization failed: {0}", ex.what()));
        }
    }
}

void GloveApplication::AddFacet(ApplicationFacet::Handle facet) {
    facets.emplace_back(std::move(facet));
}

GloveApplication::GloveApplication() {

}

GloveApplication::~GloveApplication() {

}
}