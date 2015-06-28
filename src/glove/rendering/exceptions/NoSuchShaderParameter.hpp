#pragma once

#include "glove/GloveApi.hpp"
#include "glove/GloveException.hpp"
#include "glove/rendering/ShaderParameter.hpp"
#include "glove/log/format.hpp"

namespace glove {
class GLOVE_API_EXPORT NoSuchShaderParameter : public GloveException {
  public:
    NoSuchShaderParameter(ShaderParameterSemantic semantic)
        : GloveException(fmt::format("No shader parameter mapping for semantic {0}", semantic)) {}
    NoSuchShaderParameter(ShaderParameterSemantic semantic, const char* file, int line)
        : GloveException(fmt::format("No shader parameter mapping for semantic {0}", semantic), file, line) {}

    NoSuchShaderParameter(const std::string& name)
            : GloveException(fmt::format("No shader parameter mapping for {0}", name)) {}
    NoSuchShaderParameter(const std::string& name, const char* file, int line)
            : GloveException(fmt::format("No shader parameter mapping for {0}", name), file, line) {}
};

} /* namespace glove */