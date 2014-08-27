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

#include "core/GloveFwd.h"
#include "core/GloveObject.h"
#include "IRenderable.h"

namespace glove {

class Mesh : public GloveObject, IRenderable {
public:
	Mesh(MeshDataPtr meshData, ShaderPtr shader);
	virtual ~Mesh();

	void SetMeshData(MeshDataPtr meshData);
	void SetShader(ShaderPtr shader);

	void GenerateAttribAssociations();

	virtual void Render();

protected:
	GLuint vertexArrayId;

	MeshDataPtr meshData;
	ShaderPtr shader;
};

} /* namespace glove */

#endif /* MESHRENDERER_H_ */
