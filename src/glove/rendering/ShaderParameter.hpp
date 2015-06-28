#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "glove/CommonTypes.hpp"
#include "glove/GloveApi.hpp"

namespace glove {
enum class ShaderParameterSemantic { Position, UV0 };
std::ostream& operator<<(std::ostream& stream, const ShaderParameterSemantic& shaderParameterSemantic);

/**
* A shader parameter describes a single input parameter to a VertexShader.
*
* @link VertexBindingFactory VertexBindingFactories @endlink use this information to create @link VertexBinding
* VertexBindings @endlink from a ShaderParameterMap.
*/
struct GLOVE_API_EXPORT ShaderParameter {
    ShaderParameter(uint8 attributeIndex, ShaderParameterSemantic semantic, std::string name)
        : attributeIndex(attributeIndex), semantic(semantic), name(name) {}

    uint8 attributeIndex;
    ShaderParameterSemantic semantic;
    std::string name;
};

/**
* A ShaderParameterMap is a collection of @link ShaderParameter ShaderParameters @endlink and allows to query
* attribute indices using either attribute semantics or an attribute name.
*/
struct GLOVE_API_EXPORT ShaderParameterMap {
  public:
    /// Default constructor reserves two slots in the parameters vector.
    ShaderParameterMap() { parameters.reserve(2); }
    /// Reserves @p numParams slots in the parameters vector.
    ShaderParameterMap(uint8 numParams) { parameters.reserve(numParams); }

    void AddParameter(const ShaderParameter& shaderParameter);
    void AddParameter(ShaderParameter&& shaderParameter);

    /**
     * Queries the internal ShaderParameter collection for the first parameter which hash @p semantic
     * ShaderParameterSemantic.
     * Throws if no parameter mapping for @p semantic could be found.
     */
    uint8 GetAttributeIndexFor(ShaderParameterSemantic semantic) const;

    /**
     * Queries the internal ShaderParameter collection for the first parameter whose name is @p name.
     * Throws if no parameter mapping for @p name could be fond.
     */
    uint8 GetAttributeIndexFor(const std::string& name) const;

  private:
    std::vector<ShaderParameter> parameters;
};

} /* namespace glove */