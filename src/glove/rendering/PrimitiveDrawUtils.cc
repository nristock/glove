#include "glove/rendering/PrimitiveDrawUtils.hpp"
#include "glove/rendering/Material.hpp"
#include "glove/rendering/PrimitiveDrawInterface.hpp"

#include "glove/world/scene/SceneProxy.hpp"
#include "glove/rendering/Shader.hpp"
#include "glove/rendering/VertexBinding.hpp"

using namespace BlueDwarf;

struct MeshVertex {
    float x, y, z;
    float u, v;
    MeshVertex(float x, float y, float z, float u, float v) : x(x), y(y), z(z), u(u), v(v) {}
};

class MeshMaterialProxy : public MaterialProxy {
  public:
    MeshMaterialProxy(const ShaderProgram::Handle& shaderProgram) : MaterialProxy(shaderProgram, {}) {
        textureUniform = TextureUniformParameter::Handle{
            new TextureUniformParameter{shaderProgram->GetUniformParameterIndex("tex"), nullptr}};
        uniformParameters.push_back(textureUniform);
    }

    void UpdateTexture(Texture2D::Handle texture) { textureUniform->SetTexture(texture); }

  private:
    TextureUniformParameter::Handle textureUniform;
};

static const char* VERTEX_SHADER = "#version 140\n"
                                   "\n"
                                   "uniform mat4 MatMVP;\n"
                                   "\n"
                                   "in vec3 InPosition;\n"
                                   "in vec2 InUV;\n"
                                   //"in vec4 in_Color;\n"
                                   //"in vec2 in_uv;\n"
                                   "out vec2 TexCoord;\n"
                                   "\n"
                                   "void main(void)\n"
                                   "{\n"
                                   " gl_Position = vec4(InPosition, 1);\n"
                                   " TexCoord = InUV;\n"
                                   //" ex_uv = in_uv;\n"
                                   "}";

static const char* FRAG_SHADER = "#version 140\n"
                                 "\n"
                                 "in vec2 TexCoord;\n"
                                 "out vec4 out_Color;\n"
                                 "\n"
                                 "uniform sampler2D tex;\n"
                                 "\n"
                                 "void main(void)\n"
                                 "{\n"
                                 //" out_Color = texture(tex, ex_uv).rgb;\n"
                                 " out_Color = texture(tex, TexCoord);\n"
                                 "}";

namespace BlueDwarf {
void PrimitiveDrawUtils::DrawFullscreenQuad(RenderCommandList& cmdList, Texture2D::Handle texture) {
    fullscreenQuad->Draw(cmdList, texture);
}

PrimitiveDrawUtils::PrimitiveDrawUtils(RenderResourceFactory& resourceFactory) {
    fullscreenQuad = std::make_shared<FullscreenQuad>();
    fullscreenQuad->CreateResources(resourceFactory);
}

void FullscreenQuad::CreateResources(const RenderResourceFactory& resourceFactory) {
    ShaderParameterMap shaderParameterMap{1};
    shaderParameterMap.AddParameter({0, ShaderParameterSemantic::Position, "InPosition"});
    shaderParameterMap.AddParameter({1, ShaderParameterSemantic::UV0, "InUV"});

    VertexShader::Handle vertexShader = resourceFactory.CreateVertexShader(VERTEX_SHADER, shaderParameterMap);
    FragmentShader::Handle fragmentShader = resourceFactory.CreateFragmentShader(FRAG_SHADER);
    ShaderProgram::Handle shaderProgram = resourceFactory.CreateShaderProgram(vertexShader, fragmentShader);

    materialProxy = std::shared_ptr<MeshMaterialProxy>{new MeshMaterialProxy(shaderProgram)};

    meshIndexBuffer = std::unique_ptr<GenericIndexBufferWrapper>(new GenericIndexBufferWrapper(resourceFactory));
    std::vector<ushort> indices{0, 1, 2, 2, 0, 3};
    meshIndexBuffer->SetIndices(std::move(indices));

    meshVertexBuffer = std::unique_ptr<GenericVertexBufferWrapper>(new GenericVertexBufferWrapper(resourceFactory));
    std::vector<MeshVertex> vertices{MeshVertex{-1, -1, 0, 0, 0},
                                     MeshVertex{-1, 1, 0, 0, 1},
                                     MeshVertex{1, 1, 0, 1, 1},
                                     MeshVertex{1, -1, 0, 1, 0}};
    meshVertexBuffer->SetVertices(std::move(vertices));

    vertexBindingFactory.SetVertexStreams({meshVertexBuffer->GetHardwareResource()});

    VertexLayout& vertexLayout = vertexBindingFactory.GetVertexLayout();
    vertexLayout.AddElement({0, 0, sizeof(float) * 3 + sizeof(float)*2, VertexElementType::Float3, ShaderParameterSemantic::Position});
    vertexLayout.AddElement({sizeof(float) * 3, 0, sizeof(float) * 3 + sizeof(float)*2, VertexElementType::Float2, ShaderParameterSemantic::UV0});

    vertexBinding = vertexBindingFactory.CreateBinding(
        materialProxy->GetShaderProgram()->GetVertexShader()->GetParameterMap(), resourceFactory);
};

void FullscreenQuad::Draw(RenderCommandList& cmdList, Texture2D::Handle texture) {
    materialProxy->UpdateTexture(texture);

    cmdList.EnableVertexBinding(vertexBinding);

    MeshBatchElement quadBatchElement{meshIndexBuffer->GetHardwareResource(), 2, 0, 5, glm::mat4()};
    auto dummySceneView = SceneViewBuilder::OrthogonalProjectionView(1.0).SetViewRect({0, 0, 800, 600}).Finalize();
    materialProxy->SetMesh(cmdList, dummySceneView, quadBatchElement);

    cmdList.DrawIndexed(meshIndexBuffer->GetHardwareResource(), 0, 5);
}
}