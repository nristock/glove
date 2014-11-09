#include <iostream>
#include <chrono>
#include <vector>

#include <glm/glm.hpp>
#include <core/GloveEnvironment.h>

#include "core/PluginLoader.h"
#include "core/GloveCore.h"
#include "graph/Scenegraph.h"
#include "graph/GameObject.h"
#include "shader/Material.h"
#include "shader/pyshed/PyShedLoader.h"
#include "rendering/mesh/Mesh.h"
#include "rendering/mesh/opengl/GLManagedMesh.h"

#define VF_MANAGED_DATA
#include "rendering/vertex/VertexFundamentals.h"

#include "log/Log.h"
#include "pitamem/MemoryProfile.h"

int main(int argc, const char** argv) {
	using namespace glove;
	logging::InitLoggingSystem();
	logging::GloveLogger lg;

	GloveCorePtr gcore = std::make_shared<GloveCore>(argc, argv);
	gcore->Init(argc, argv);
	
	std::vector<vertexlayouts::PositionColor> vertices;
	vertexlayouts::PositionColor v1 = {glm::vec3(-.8f, -.8f, 0), glm::vec4(1, 0, 0, 1)};
	vertexlayouts::PositionColor v2 = { glm::vec3(.8f, -.8f, 0), glm::vec4(0, 1, 0, 1) };
	vertexlayouts::PositionColor v3 = { glm::vec3(.8f, .8f, 0), glm::vec4(0, 0, 1, 1) };
	vertexlayouts::PositionColor v4 = { glm::vec3(-.8f, .8f, 0), glm::vec4(1, 0, 0, 1) };
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	//meshData->SetVertices(vertices);
	//meshData->UploadData();
	
	//GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	ShaderProgramPointer shader = gcore->GetPyshedLoader()->LoadPysehdShader(gEnv->MakeDataPath(std::string("data/DefaultShader.pyshed")));
	MaterialPtr material = MaterialPtr(new Material(shader));
	
	ScenegraphPtr graph = gcore->GetScenegraph();
	auto go = graph->CreateSimpleGameObject();
	//IndexedMesh m(meshData, material, go);
	std::shared_ptr<ManagedMesh<vertexlayouts::PositionColor>> m =
            std::shared_ptr<ManagedMesh<vertexlayouts::PositionColor>>(
                    new GLManagedMesh<vertexlayouts::PositionColor>(
                            gcore->GetRenderer(),
                            gcore->GetGpuBufferManager(),
                            material
                    )
            );
    auto mm = std::dynamic_pointer_cast<GLManagedMesh<vertexlayouts::PositionColor>>(m);

    mm->AddVAO(0, gcore->GetRenderer());
    GameComponentPtr gp = std::dynamic_pointer_cast<GameComponent>(m);

	go->AddComponent(gp);

	//m->GetVertexData()->GetVertexLayout()->AddElement(0, 0, VAT_FLOAT3, VAS_POSITION);
	//m->GetVertexData()->GetVertexLayout()->AddElement(0, VertexAttribute::GetSize(VAT_FLOAT3), VAT_FLOAT4, VAS_COLOR);
	//m->GetVertexData()->SetVertexCount(4);

	//GPUBufferPtr vbuf = gcore->GetGpuBufferManager()->CreateVertexBuffer(BU_STATIC);
	//vbuf->WriteData(sizeof(Vertices), Vertices);
	//m->GetVertexData()->SetBufferBinding(0, vbuf);
	m->GetManagedVertexData()->SetVertices(vertices);
	m->GetManagedVertexData()->FlushBuffer();

	m->CreateIndexData();
	//GPUBufferPtr ibuf = m->GetIndexData()->GetBuffer();
	//ibuf->WriteData(6 * sizeof(GLuint), indices);
	//m->GetIndexData()->SetIndexCount(6);
	//m->Refresh();
	m->GetManagedIndexData()->SetIndices(indices);
	m->GetManagedIndexData()->FlushBuffer();
	m->Refresh();

	auto parent = graph->CreateSimpleGameObject();
	parent->AttachChild(go);
		
//	typedef std::chrono::steady_clock::time_point timep;
//	timep t1 = std::chrono::steady_clock::now();
//	timep p1 = std::chrono::steady_clock::now();

//	float move = 0;
	gcore->EnterMainLoop();
	/*while (true) {
		move += .001f;
		parent->GetTransform().SetPosition(glm::vec3(sin(move), 0, 0));
		go->GetTransform().SetPosition(glm::vec3(0, sin(move), 0));

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		
		gcore->Update();
		gcore->Render(graph);
	}*/
}