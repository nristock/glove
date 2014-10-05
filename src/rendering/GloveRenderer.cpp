#include "GloveRenderer.h"

#include <sstream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/GloveException.h"
#include "graph/Scenegraph.h"
#include "rendering/Camera.h"
#include "rendering/IRenderable.h"
#include "rendering/FrameData.h"
#include "log/Log.h"
#include "GloveWindow.h"

#include "buffers/GPUBuffer.h"
#include "rendering/vertex/IndexData.h"
#include "rendering/vertex/VertexData.h"
#include "rendering/vertex/VertexLayout.h"
#include "rendering/mesh/IMesh.h"
#include "rendering/mesh/opengl/GLBaseMesh.h"
#include "shader/ShaderProgram.h"
#include "shader/Material.h"


namespace glove {

GloveRenderer::GloveRenderer() {
	currentRenderOperation.Reset();
}

GloveRenderer::~GloveRenderer() {
	// TODO Auto-generated destructor stub
}

void GloveRenderer::Init(int windowWidth, int windowHeight, int glMajor, int glMinor, int argc, char** argv) {
	glfwSetErrorCallback(&GloveRenderer::GlfwErrorSink);
	
	if (!glfwInit()) {
		throw GloveException("GLFW Initialization failed.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	associatedWindow = GloveWindowPtr(new GloveWindow());
	associatedWindow->Init(windowWidth, windowHeight);
	associatedWindow->MakeCurrent();

	glewExperimental = GL_TRUE;
	GLenum glewInitRes = glewInit();
	if (glewInitRes != GLEW_OK) {
		throw GloveException(std::string((char*)glewGetErrorString(glewInitRes)));
	}

	OLOG(info, "Glove renderer initialized");
	OLOG(info, "GL Version: " << glGetString(GL_VERSION));
}

void GloveRenderer::Exit() {
	glfwTerminate();
}

void GloveRenderer::GlfwErrorSink(int error, const char* description) {
	LOG(logging::globalLogger, error, "GLFW Error (" << error << "): " << description);
}

void GloveRenderer::RenderScene(ScenegraphPointer scenegraph, FrameData& frameData) {
	frameData.viewProjectionMatrix = associatedWindow->GetProjMatrix() * scenegraph->GetMainCamera()->GetViewMatrix();
	
	scenegraph->IterateGameObjects([&](GameObjectPtr gameObject){
		gameObject->IterateRenderableComponents([&](const IRenderablePtr& renderable) {
			renderable->SetupRender(currentRenderOperation, frameData);
			RenderObject(currentRenderOperation, frameData, gameObject);
			renderable->PostRender(currentRenderOperation, frameData);
		});			
	});

	associatedWindow->SwapBuffers();
}

void GloveRenderer::RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GameObjectPtr& gameObject) {
	renderOp.material->SetMaterialAttribute(MMA_MAT_MVP, gameObject->GetTransform().GetGlobalTransform() * frameData.viewProjectionMatrix);

	if (renderOp.indexData == nullptr) {
		glDrawArrays(GL_TRIANGLES, 0, renderOp.vertexData->GetVertexCount());
	}
	else {
		renderOp.indexData->GetBuffer()->Bind();
		glDrawElements(GL_TRIANGLES, renderOp.indexData->GetIndexCount(), GL_UNSIGNED_INT, 0);
	}
}

void GloveRenderer::CreateVertexAttributeMappings(IMesh* mesh) {
	GLBaseMesh* oglMesh = dynamic_cast<GLBaseMesh*>(mesh);
	VertexDataPtr vertexData = mesh->GetVertexData();
	ShaderProgramPtr shader = mesh->GetShader();

	glBindVertexArray(oglMesh->GetVertexArrayId());

	size_t stride = 0;
	for (auto vertexAttribute : vertexData->GetVertexLayout()->GetAttributes()) {
		stride += vertexAttribute.GetSize();
	}

	for (auto vertexAttribute : vertexData->GetVertexLayout()->GetAttributes()) {
		GPUBufferPtr gpuBuffer = vertexData->GetBuffer(vertexAttribute.GetBindingSlot());
		gpuBuffer->Bind();

		GLuint attribIndex = shader->GetVertexAttributePosition(vertexAttribute.GetSemantic());
		if (attribIndex < 0) {
			OLOG(error, "Vertex attribute in buffer not mapped to shader attribute index.");
			continue;
		}

		glVertexAttribPointer(attribIndex, 
			vertexAttribute.GetNumberOfComponents(), 
			TranslateVertexAttributeType(vertexAttribute.GetType()), 
			GL_FALSE, 
			stride, 
			(void*)vertexAttribute.GetOffset());
		glEnableVertexAttribArray(attribIndex);
	}
}

GLenum GloveRenderer::TranslateVertexAttributeType(VertexAttributeType attribType) {
	switch (attribType) {
	case VAT_FLOAT3:
	case VAT_FLOAT4:
		return GL_FLOAT;
	}
}

} /* namespace glove */
