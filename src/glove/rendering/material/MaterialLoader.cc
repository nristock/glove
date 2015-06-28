#include <glove/rendering/RenderThread.hpp>
#include <glove/rendering/Shader.hpp>
#include "glove/rendering/material/MaterialLoader.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"

namespace glove {

static const char* VERTEX_SHADER = "#version 140\n"
        "\n"
        "uniform mat4 MatMVP;\n"
        "\n"
        "in vec3 InPosition;\n"
        //"in vec2 InUV;\n"
        //"out vec2 TexCoord;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        " gl_Position = vec4(InPosition, 1);\n"
        //" TexCoord = InUV;\n"
        "}";

static const char* FRAG_SHADER = "#version 140\n"
        "\n"
        //"in vec2 TexCoord;\n"
        "out vec4 out_Color;\n"
        "\n"
        //"uniform sampler2D tex;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        //" out_Color = texture(tex, TexCoord);\n"
        " out_Color = vec4(1,1,1,1);\n"
        "}";

void MaterialLoadTask::Execute() {
    L_INFO(fmt::format("Loading material {0:x}...", materialName.GetHash()));

    RenderDispatcher::EnsureRenderThread();

    ShaderParameterMap shaderParameterMap{1};
    shaderParameterMap.AddParameter({0, ShaderParameterSemantic::Position, "InPosition"});
    //shaderParameterMap.AddParameter({1, ShaderParameterSemantic::UV0, "InUV"});

    VertexShader::Handle vertexShader = resourceFactory->CreateVertexShader(VERTEX_SHADER, shaderParameterMap);
    FragmentShader::Handle fragmentShader = resourceFactory->CreateFragmentShader(FRAG_SHADER);
    ShaderProgram::Handle shaderProgram = resourceFactory->CreateShaderProgram(vertexShader, fragmentShader);

    material = std::make_shared<BasicMaterial>(shaderProgram);

    L_INFO(fmt::format("Done loading material {0:x}.", materialName.GetHash()));
}

MaterialFuture MaterialLoader::Load(StringId materialName, Handle<RenderResourceFactory> resourceFactory) {
    logger.Info(fmt::format("Creating async material load task for {0} ({1:x})", materialName.Resolve(), materialName.GetHash()), M_TAG);

    auto loadTask = std::make_shared<MaterialLoadTask>(materialName, resourceFactory);
    auto poolTask = RenderDispatcher::DispatchTask(loadTask);

    return MaterialFuture{loadTask, poolTask};
}
}