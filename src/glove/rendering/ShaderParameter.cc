#include "glove/rendering/ShaderParameter.hpp"
#include "glove/rendering/exceptions/NoSuchShaderParameter.hpp"

namespace glove {

std::ostream& operator<<(std::ostream& stream, const ShaderParameterSemantic& shaderParameterSemantic) {
    stream << static_cast<ushort>(shaderParameterSemantic);
    return stream;
}

uint8 ShaderParameterMap::GetAttributeIndexFor(ShaderParameterSemantic semantic) const {
    auto shaderParameter =
        std::find_if(parameters.begin(), parameters.end(),
                     [&semantic](const ShaderParameter& param) { return param.semantic == semantic; });

    if (shaderParameter != parameters.end()) {
        return shaderParameter->attributeIndex;
    }

    GLOVE_THROW(NoSuchShaderParameter, semantic);
}

uint8 ShaderParameterMap::GetAttributeIndexFor(const std::string& name) const {
    auto shaderParameter = std::find_if(parameters.begin(), parameters.end(),
                                        [&name](const ShaderParameter& param) { return param.name == name; });

    if (shaderParameter != parameters.end()) {
        return shaderParameter->attributeIndex;
    }

    GLOVE_THROW(NoSuchShaderParameter, name);
}

void ShaderParameterMap::AddParameter(ShaderParameter&& shaderParameter) {
    parameters.push_back(std::forward<ShaderParameter>(shaderParameter));
}

void ShaderParameterMap::AddParameter(const ShaderParameter& shaderParameter) {
    parameters.push_back(shaderParameter);
}
}