#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/DwarfException.hpp"
#include "glove/rendering/ShaderParameter.hpp"
#include "glove/log/format.hpp"

namespace BlueDwarf {
class BD_API_EXPORT NoSuchShaderParameter : public DwarfException {
  public:
    NoSuchShaderParameter(ShaderParameterSemantic semantic)
        : DwarfException(fmt::format("No shader parameter mapping for semantic {0}", semantic)) {}
    NoSuchShaderParameter(ShaderParameterSemantic semantic, const char* file, int line)
        : DwarfException(fmt::format("No shader parameter mapping for semantic {0}", semantic), file, line) {}

    NoSuchShaderParameter(const std::string& name)
            : DwarfException(fmt::format("No shader parameter mapping for {0}", name)) {}
    NoSuchShaderParameter(const std::string& name, const char* file, int line)
            : DwarfException(fmt::format("No shader parameter mapping for {0}", name), file, line) {}
};

} /* namespace BlueDwarf */