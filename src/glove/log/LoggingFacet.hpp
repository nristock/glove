#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/application/DwarfApplication.hpp"
#include "glove/log/MessageProcessors.hpp"

namespace BlueDwarf {
class BD_API_EXPORT LoggingFacet : public ApplicationFacet {
  public:
    LoggingFacet() : ApplicationFacet("LoggingFacet") {}

    virtual void Configure() override {
        auto consoleOutProcessor = std::make_shared<ConsoleOutProcessor>();
        auto formatter = std::make_shared<DefaultFormatterProcessor>(consoleOutProcessor);
        auto asyncProcessor = std::make_shared<AsyncProcessor>(formatter);

        Logger::SetDefaultMessageProcessor(asyncProcessor);

        L_INFO("----------- Logging facet configured -----------");
    }
};

}