/*
 * MeshRenderer.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <memory>
#include "../core/GloveObject.h"
#include "../shader/MeshData.h"
#include "../shader/Shader.h"
#include "IRenderable.h"

namespace glove {
namespace gl {
namespace rendering {

class Mesh : public core::GloveObject, IRenderable {
public:
	Mesh(shader::MeshDataPtr meshData, shader::ShaderPtr shader);
	virtual ~Mesh();

	void SetMeshData(shader::MeshDataPtr meshData);
	void SetShader(shader::ShaderPtr shader);

	void GenerateAttribAssociations();

	virtual void Render();

protected:
	GLuint vertexArrayId;

	shader::MeshDataPtr meshData;
	shader::ShaderPtr shader;
};

typedef std::shared_ptr<Mesh> MeshRendererPtr;

} /* namespace rendering */
} /* namespace gl */
} /* namespace glove */

#endif /* MESHRENDERER_H_ */
