#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "core/GloveCore.h"
#include "shader/Shader.h"
#include "rendering/Mesh.h"
#include "rendering/MeshData.h"
#include "rendering/IndexedMesh.h"
#include "rendering/IndexedMeshData.h"
#include "buffers/VertexAttributeBuffer.h"
#include "graph/Scenegraph.h"
#include "graph/GameObject.h"

#include <glm/glm.hpp>

#include "log/log.h"

int main(int argc, char** argv) {
	using namespace glove;

	logging::InitLoggingSystem();
	logging::GloveLogger lg;

	auto gcore = new GloveCore();
	gcore->InitializeRenderingContext(argc, argv, 800, 600);

	GLfloat Vertices[] = { -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.8f, 0.0f, 1.0f,
			0.8f, -0.8f, 0.0f, 1.0f };

	GLfloat Colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f };

	IndexedMeshDataPtr mdp = IndexedMeshDataPtr(new IndexedMeshData(3));
	VABPtr verts = VABPtr(new VertexAttributeBuffer(GL_STATIC_DRAW, 0, 0));
	verts->FillData(sizeof(Vertices), Vertices);
	verts->DefineVertexLayout(MVA_POSITIONS, 4, GL_FLOAT, GL_FALSE, 0);
	VABPtr cols = VABPtr(new VertexAttributeBuffer(GL_STATIC_DRAW, 0, 0));
	cols->FillData(sizeof(Colors), Colors);
	cols->DefineVertexLayout(MVA_COLORS, 4, GL_FLOAT, GL_FALSE, 0);



	mdp->AddGPUBuffer(verts);
	mdp->AddGPUBuffer(cols);
	GLuint indices[] = {0, 1, 2};
	mdp->SetIndices(indices, 3);

	ShaderPtr shader = ShaderPtr(new Shader(2));
	shader->AttachShader(0, GL_VERTEX_SHADER, "data/DefaultShader.vertex");
	shader->AttachShader(1, GL_FRAGMENT_SHADER, "data/DefaultShader.fragment");
	shader->CreateProgram();
	shader->MapVertexAttribute(MVA_POSITIONS, 0);
	shader->MapVertexAttribute(MVA_COLORS, 1);

	IndexedMesh m = IndexedMesh(mdp, shader);

	Scenegraph graph;

	auto go = graph.CreateGameObject();

	while (true) {
		glutMainLoopEvent();

		glClear(GL_COLOR_BUFFER_BIT);

		m.Render();

		glutSwapBuffers();
	}

}
