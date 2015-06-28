#pragma once

#include "glove/application/DwarfApplication.hpp"
#include "glove/natex/DirectoryExtensionSearcher.hpp"

using namespace BlueDwarf;

class NatexFacetConfigurator : public ApplicationFacet {
  public:

    NatexFacetConfigurator(const std::shared_ptr<NatexFacet>& natexFacet) : ApplicationFacet("NatexFacetConfigurator"), natexFacet(natexFacet){}

    virtual void Configure() override {
        auto directoryExtensionSearcher = std::make_shared<DirectoryExtensionSearcher>("data/natex");
        natexFacet->AddExtensionSearcher(directoryExtensionSearcher);
    }

  private:
    std::shared_ptr<NatexFacet> natexFacet;
};