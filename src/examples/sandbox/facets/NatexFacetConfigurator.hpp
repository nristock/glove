#pragma once

#include "glove/application/GloveApplication.hpp"
#include "glove/natex/DirectoryExtensionSearcher.hpp"

using namespace glove;

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