#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include "core/GloveCore.h"
#include "graph/Scenegraph.h"
#include "graph/GameObject.h"
#include "shader/Shader.h"
#include "rendering/Mesh.h"
#include "rendering/MeshData.h"
#include "rendering/IndexedMesh.h"
#include "rendering/IndexedMeshData.h"
#include "buffers/VertexAttributeBuffer.h"

#include "log/Log.h"
#include "memory/GloveMemory.h"

int main(int argc, char** argv) {
	using namespace glove;
	using namespace memory_internal;

	logging::InitLoggingSystem();
	logging::GloveLogger lg;

	auto gcore = new GloveCore();
	gcore->Init(argc, argv);
	
	GLfloat Vertices[] = { -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.8f, 0.0f, 1.0f,
		0.8f, -0.8f, 0.0f, 1.0f };

	GLfloat Colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f };

	IndexedMeshDataPtr mdp(new IndexedMeshData(3));
	VABPtr verts(new VertexAttributeBuffer(GL_STATIC_DRAW, 0, 0));
	verts->FillData(sizeof(Vertices), Vertices);
	verts->DefineVertexLayout(MVA_POSITIONS, 4, GL_FLOAT, GL_FALSE, 0);
	VABPtr cols(new VertexAttributeBuffer(GL_STATIC_DRAW, 0, 0));
	cols->FillData(sizeof(Colors), Colors);
	cols->DefineVertexLayout(MVA_COLORS, 4, GL_FLOAT, GL_FALSE, 0);
	
	mdp->AddGPUBuffer(verts);
	mdp->AddGPUBuffer(cols);
	GLuint indices[] = { 0, 1, 2 };
	mdp->SetIndices(indices, 3);

	ShaderPtr shader(new Shader(2));
	shader->AttachShader(0, GL_VERTEX_SHADER, "data/DefaultShader.vertex");
	shader->AttachShader(1, GL_FRAGMENT_SHADER, "data/DefaultShader.fragment");
	shader->CreateProgram();
	shader->MapVertexAttribute(MVA_POSITIONS, 0);
	shader->MapVertexAttribute(MVA_COLORS, 1);

	IndexedMesh m(mdp, shader);

	Scenegraph graph;

	auto go = graph.CreateGameObject();

	typedef std::chrono::steady_clock::time_point timep;
	timep t1 = std::chrono::steady_clock::now();
	
	while (true) {
		timep t2 = std::chrono::steady_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		if (time_span.count() > 10) {
			t1 = std::chrono::steady_clock::now();
			LOG(logging::globalLogger, info, memory_internal::DumpList());
		}

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		m.Render();

		gcore->Render();
	}

	gcore->Exit();
}
