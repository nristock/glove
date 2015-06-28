#include "glove/application/DwarfApplication.hpp"
#include "glove/world/World.hpp"

namespace BlueDwarf {

void DwarfApplication::Run() {
    Configure();
    Bootstrap();
    Initialize();

    RunLoop();

    Finalize();
}

void DwarfApplication::Configure() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Configure Facet: {0}", facet->ToString()))
        try {
            facet->Configure();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet configuration failed: {0}", ex.what()));
        }
    }
}

void DwarfApplication::Bootstrap() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Bootstrapping Facet: {0}", facet->ToString()))
        try {
            facet->Bootstrap();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet bootstrap failed: {0}", ex.what()));
        }
    }
}

void DwarfApplication::Initialize() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Initialize Facet: {0}", facet->ToString()))
        try {
            facet->Initialize();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet initialization failed: {0}", ex.what()));
        }
    }
}

void DwarfApplication::RunLoop() {
}

void DwarfApplication::Finalize() {
    for(auto& facet : facets) {
        L_INFO(fmt::format("Finalize Facet: {0}", facet->ToString()))
        try {
            facet->Finalize();
        } catch (const std::exception& ex) {
            L_ERROR(fmt::format("Facet finalization failed: {0}", ex.what()));
        }
    }
}

void DwarfApplication::AddFacet(ApplicationFacet::Handle facet) {
    facets.emplace_back(std::move(facet));
}

DwarfApplication::DwarfApplication() {

}

DwarfApplication::~DwarfApplication() {

}
}