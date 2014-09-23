#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include "core/GloveCore.h"
#include "graph/Scenegraph.h"
#include "graph/GameObject.h"
#include "shader/ShaderProgram.h"
#include "shader/Material.h"
#include "shader/pyshed/PyShedLoader.h"
#include "rendering/Mesh.h"
#include "rendering/MeshData.h"
#include "rendering/IndexedMesh.h"
#include "rendering/IndexedMeshData.h"
#include "buffers/VertexAttributeBuffer.h"
#include "rendering/GloveWindow.h"

#include "log/Log.h"
#include "memory/GloveMemory.h"

int main(int argc, char** argv) {
	using namespace glove;
	using namespace memory_internal;

	logging::InitLoggingSystem();
	logging::GloveLogger lg;

	auto gcore = new GloveCore();
	gcore->Init(argc, argv);
	
	GLfloat Vertices[] = { 
		-0.8f, -0.8f, 0, 
		0.8f, -0.8f, 0,
		0.8f, 0.8f, 0,
		-0.8f, 0.8f, 0
	};

	GLfloat Colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f };

	IndexedMeshDataPtr mdp(new IndexedMeshData(4));
	VABPtr verts(new VertexAttributeBuffer(GL_STATIC_DRAW, 0, 0));
	verts->FillData(sizeof(Vertices), Vertices);
	verts->DefineVertexAttribute(MVA_POSITIONS, 3, GL_FLOAT, GL_FALSE, 0);
	VABPtr cols(new VertexAttributeBuffer(GL_STATIC_DRAW, 0, 0));
	cols->FillData(sizeof(Colors), Colors);
	cols->DefineVertexAttribute(MVA_COLORS, 4, GL_FLOAT, GL_FALSE, 0);
	
	mdp->AddGPUBuffer(verts);
	mdp->AddGPUBuffer(cols);
	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
	mdp->SetIndices(indices, 6);

	ShaderProgramPointer shader = gcore->GetPyshedLoader()->LoadPysehdShader(gcore->MakeDataPath(std::string("data/DefaultShader.pyshed")));
	MaterialPtr material = MaterialPtr(new Material(shader));
	
	ScenegraphPtr graph = gcore->GetScenegraph();
	auto go = graph->CreateGameObject();
	IndexedMesh m(mdp, material, go);
	go->AddComponent(&m);

	auto parent = graph->CreateGameObject();
	parent->AttachChild(go);
		
	typedef std::chrono::steady_clock::time_point timep;
	timep t1 = std::chrono::steady_clock::now();
	timep p1 = std::chrono::steady_clock::now();

	float move = 0;
	while (true) {
		timep t2 = std::chrono::steady_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		if (time_span.count() > 20) {
			t1 = std::chrono::steady_clock::now();
			LOG(logging::globalLogger, info, memory_internal::DumpList());

			std::chrono::milliseconds time_span2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - p1);
			LOG(logging::globalLogger, info, "FrameTime: " << time_span2.count());
		}


		p1 = std::chrono::steady_clock::now();

		move += .001f;
		parent->GetTransform().SetPosition(glm::vec3(sin(move), 0, 0));
		go->GetTransform().SetPosition(glm::vec3(0, sin(move), 0));

		//parent->RefreshTransformTree();

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		
		gcore->Render(graph);
	}

	gcore->Exit();
}
