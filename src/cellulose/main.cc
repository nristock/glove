#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glove/GloveEnvironment.h>
#include <glove/GloveCore.h>
#include <glove/log/Log.h>
#include <glove/natex/Natex.h>
#include <glove/natex/ISubsystem.h>
#include <glove/natex/ISubsystemInstanceRegistry.h>
#include <glove/rendering/Rendering.h>
#include <glove/rendering/RenderingInterfaces.h>
#include <glove/rendering/vertex/DynamicVertexData.h>
#include <glove/rendering/vertex/DynamicIndexData.h>
#include <glove/rendering/vertex/VertexLayouts.h>
#include <glove/graph/Scenegraph.h>
#include <glove/graph/gamecomponent/GameComponent.h>
#include <glove/rendering/gamecomponent/OrthoCamera.h>
#include <glove/rendering/gamecomponent/MeshRenderer.h>
#include <glove/rendering/gamecomponent/factories/CameraComponentFactory.h>

int main(int argc, const char** argv) {
    using namespace glove;
    logging::InitLoggingSystem();
    logging::GloveLogger lg;

    GloveCorePtr gcore = std::make_shared<GloveCore>(argc, argv);
    gcore->Init(argc, argv);

    std::vector<VertexLayouts::PositionColor> vertices;
    VertexLayouts::PositionColor v1 = {glm::vec3(-.8f, -.8f, 0), glm::vec4(1, 0, 0, 1)};
    VertexLayouts::PositionColor v2 = {glm::vec3(.8f, -.8f, 0), glm::vec4(0, 1, 0, 1)};
    VertexLayouts::PositionColor v3 = {glm::vec3(.8f, .8f, 0), glm::vec4(0, 0, 1, 1)};
    VertexLayouts::PositionColor v4 = {glm::vec3(-.8f, .8f, 0), glm::vec4(1, 0, 0, 1)};
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    std::vector<unsigned int> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    ISubsystemInstanceRegistryPtr subsystemRegistry = gcore->GetSubsystemInstanceRegistry();
    ISubsystemPtr protoSubsystem = subsystemRegistry->GetUniqueSubsystemOfType(IRenderSubsystem::subsystemType);
    IRenderSubsystemPtr renderSubsystem = std::dynamic_pointer_cast<IRenderSubsystem>(protoSubsystem);

    WindowConstructionHints windowConstructionHints(ScreenPoint(0, 0), ScreenDimensions(800, 600), "Glove Windooow");
    IRendererPtr renderer = renderSubsystem->GetRendererFactory()->CreateRenderer(windowConstructionHints);

    IShaderPtr vertexShader = renderSubsystem->GetShaderFactory(renderer)
                                  ->CreateVertexShader(gEnv->MakeDataPath("data/DefaultShader.vertex"));
    IShaderPtr fragmentShader = renderSubsystem->GetShaderFactory(renderer)
                                    ->CreateFragmentShader(gEnv->MakeDataPath("data/DefaultShader.fragment"));

    std::list<IShaderPtr> shaderList;
    shaderList.push_back(vertexShader);
    shaderList.push_back(fragmentShader);
    IShaderProgramPtr shaderProgram = renderSubsystem->GetShaderProgramFactory()->CreateShaderProgram(shaderList);
    IVertexAttributeMappingPtr vertexAttributeMapping = shaderProgram->GetVertexAttributeMapping();
    vertexAttributeMapping->MapAttribute(VertexAttributeSemantic::POSITION, 0);
    vertexAttributeMapping->MapAttribute(VertexAttributeSemantic::COLOR, 1);

    IMaterialPtr material = renderSubsystem->GetMaterialFactory()->CreateMaterial(shaderProgram);
    IMaterialAttributePtr mvp = material->GetMaterialAttribute("mvpmat");

    IIndexDataPtr indexData(new DynamicIndexData<unsigned int>(renderSubsystem->GetGpuBufferFactory(renderer)));
    IVertexDataPtr vertexData(new DynamicVertexData<VertexLayouts::PositionColor>(
        renderSubsystem->GetGpuBufferFactory(renderer), VertexLayouts::PositionColor::GetLayout()));

    std::shared_ptr<DynamicIndexData<unsigned int>> dynIndexData =
        std::dynamic_pointer_cast<DynamicIndexData<unsigned int>>(indexData);
    std::shared_ptr<DynamicVertexData<VertexLayouts::PositionColor>> dynVertexData =
        std::dynamic_pointer_cast<DynamicVertexData<VertexLayouts::PositionColor>>(vertexData);

    dynIndexData->SetIndices(indices);
    dynIndexData->FlushBuffer();
    dynVertexData->SetVertices(vertices);
    dynVertexData->FlushBuffer();

    IMeshPtr mesh = renderSubsystem->GetMeshFactory(renderer)->CreatedIndexedMesh(material, vertexData, indexData);

    ScenegraphHandle graph = std::make_shared<Scenegraph>();

    GameObjectHandle cameraObject = graph->CreateSimpleGameObject();
    CameraBaseHandle camera = glove::ComponentFactories::CameraComponentFactory::CreateOrthographicCamera(2, 1);
    renderer->MapCameraToTarget(camera, renderer->GetDefaultRenderTarget());
    cameraObject->AddComponent(camera);

    GameObjectHandle meshObject = graph->CreateSimpleGameObject();
    MeshRendererHandle meshRenderer = std::make_shared<GameComponents::MeshRenderer>(mesh, renderSubsystem->GetRenderOperationFactory());
    meshObject->AddComponent(meshRenderer);


    glm::mat4 modelViewProjection = camera->GetViewProjectionMatrix() * meshObject->GetTransform().GetGlobalTransform();

    while (!renderer->GetAssociatedWindow()->CloseRequested()) {
        renderer->GetAssociatedWindow()->PollSystemEvents();
        renderer->ClearBuffers();
        renderer->RenderScene(graph, renderer->GetDefaultRenderTarget());
        renderer->SwapBuffers();
        mvp->Set(modelViewProjection);
    }
}
