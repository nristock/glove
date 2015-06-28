#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <glove/math/IntPoint.hpp>
#include <glove/rendering/ApplicationViewport.hpp>
#include <glove/rendering/SceneView.hpp>
#include <new/GLRenderHardwareInterface.hpp>

struct GLFWwindow;

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLViewportClient : public ViewportClient {
  public:
    virtual void GLFlush(const RenderTarget& renderTarget, GLRenderHardwareInterface& renderHardwareInterface) = 0;
};

class GLWindow : public GLViewportClient {
    friend class GlfwWrapper;

  public:
    GLWindow(const IntPoint& position, const IntPoint& size, const std::string& title);

    virtual ~GLWindow();

    void MakeCurrent();

    void SwapBuffers();

    virtual bool ShouldClose();

    std::string GetContextVersion() const;

    virtual void PollSystemEvents();


    virtual IntPoint GetClientArea() const ;

    virtual void Flush(const RenderTarget& renderTarget);


    virtual void GLFlush(const RenderTarget& renderTarget, GLRenderHardwareInterface& renderHardwareInterface);

    GLFWwindow* GetGlfwWindow() const;
    GLEWContext* GetGlewContext() const;

  private:
    GLFWwindow* glfwWindow;
    GLEWContext* glewContext;

    void OnKeyEvent(int key, int scancode, int action, int mods);
    void OnMouseMove(double x, double y);
    void OnMouseButton(int button, int action, int mods);
};
}
} // namespace glove