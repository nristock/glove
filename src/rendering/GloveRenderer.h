//TODO: split into interface and OGL implementation

#ifndef GLOVERENDERER_H_
#define GLOVERENDERER_H_

#include <gl/glew.h>
#include <gl/GL.h>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"
#include "core/RenderOperation.h"

#include "rendering/FrameData.h"
#include "rendering/vertex/VertexAttributeType.h"

struct GLFWwindow;

namespace glove {
class GloveWindow;

class GloveRenderer : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveRenderer")
public:
	GloveRenderer();
	virtual ~GloveRenderer();

	void Init(int windowWidth, int windowHeight, int glMajor, int glMinor, int argc, char** argv);
	void Exit();

	void RenderScene(ScenegraphPointer scenegraph, FrameData& framData);
	
	GloveWindowPtr GetWindow() const { return associatedWindow; }

	void CreateVertexAttributeMappings(IMesh* mesh);
	
private:
	GloveWindowPtr associatedWindow;
	RenderOperation currentRenderOperation;
	
	void SetViewport(int width, int height);

	static void GlfwErrorSink(int error, const char* description);	

	void RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GameObjectPtr& gameObject);
	GLenum TranslateVertexAttributeType(VertexAttributeType attribType);
};

} /* namespace glove */

#endif /* GLOVERENDERER_H_ */
