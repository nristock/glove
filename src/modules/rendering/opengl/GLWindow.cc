#include "GLWindow.h"

#include "core/GloveCore.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/format.hpp>

#include <core/events/EventBus.h>
#include <core/events/type/KeyEvent.h>
#include <core/events/type/MouseButtonEvent.h>
#include <core/events/type/MouseMoveEvent.h>
#include <core/rendering/WindowConstructionHints.h>
#include <modules/rendering/opengl/internal/GlfwWrapper.h>

namespace {

bool GLOVE_INLINE IsModifierKeyDown(int modsFlag, int keyToCheck) {
    return (modsFlag & keyToCheck) != 0;
}

bool GLOVE_INLINE IsAltKeyDown(int modsFlag) {
    return IsModifierKeyDown(modsFlag, GLFW_MOD_ALT);
}

bool GLOVE_INLINE IsCtrlKeyDown(int modsFlag) {
    return IsModifierKeyDown(modsFlag, GLFW_MOD_CONTROL);
}

bool GLOVE_INLINE IsShiftKeyDown(int modsFlag) {
    return IsModifierKeyDown(modsFlag, GLFW_MOD_SHIFT);
}

bool GLOVE_INLINE IsSuperKeyDown(int modsFlag) {
    return IsModifierKeyDown(modsFlag, GLFW_MOD_SUPER);
}
}

namespace glove {
namespace gl {

GLWindow::GLWindow(const EventBusPtr& eventBus, const WindowConstructionHints& creationHints)
    : eventBus(eventBus), viewportWidth(0), viewportHeight(0), aspectRatio(0), orthoSize(10) {
    glfwWindow = GlfwWrapper::CreateGlfwWindow(creationHints, this);
    glewContext = new GLEWContext();

    SetupViewport();
}

void GLWindow::SetupViewport() {
    int width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    SetFramebufferSize(width, height);
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(glfwWindow);
}

void GLWindow::MakeCurrent() {
    glfwMakeContextCurrent(glfwWindow);
}

bool GLWindow::CloseRequested() const {
    return glfwWindowShouldClose(glfwWindow) != 0;
}

void GLWindow::SetFramebufferSize(int width, int height) {
    viewportWidth = width;
    viewportHeight = height;

    GLFWwindow* currentContext = glfwGetCurrentContext();
    if (currentContext != glfwWindow) {
        MakeCurrent();
    }

    glViewport(0, 0, width, height);

    if (currentContext != glfwWindow) {
        glfwMakeContextCurrent(currentContext);
    }

    aspectRatio = width / height;
    projectionMat = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);
}

void GLWindow::SwapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

void GLWindow::OnKeyEvent(int key, int scancode, int action, int mods) {
    KeyAction keyAction = (action == GLFW_PRESS) ? KA_PRESS : ((action == GLFW_RELEASE) ? KA_RELEASE : KA_REPEAT);
    KeyEvent keyEvent((KeyCode)key, keyAction, IsAltKeyDown(mods), IsCtrlKeyDown(mods), IsShiftKeyDown(mods),
                      IsSuperKeyDown(mods));
    eventBus->Publish(keyEvent);
}

void GLWindow::OnMouseMove(double x, double y) {
    MouseMoveEvent moveEvent(x, y);
    eventBus->Publish(moveEvent);
}

void GLWindow::OnMouseButton(int button, int action, int mods) {
    ButtonAction buttonAction = (action == GLFW_PRESS) ? BA_PRESS : BA_RELEASE;
    MouseButtonEvent buttonEvent((MouseButton)button, buttonAction, IsAltKeyDown(mods), IsCtrlKeyDown(mods),
                                 IsShiftKeyDown(mods), IsSuperKeyDown(mods));
    eventBus->Publish(buttonEvent);
}

std::string GLWindow::GetContextVersion() const {
    return (boost::format("OpenGL %1%.%2%.%3%") % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MAJOR) %
            glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MINOR) %
            glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_REVISION)).str();
}

GLFWwindow* GLWindow::GetGlfwWindow() const {
    return glfwWindow;
}

glm::mat4 GLWindow::GetProjectionMatrix() const {
    return projectionMat;
}

GLEWContext* GLWindow::GetGlewContext() const {
    return glewContext;
}

ScreenPoint GLWindow::GetPosition() const {
    ScreenPoint position;
    glfwGetWindowPos(glfwWindow, &position.x, &position.y);

    return position;
}

Dimensions GLWindow::GetDimensions() const {
    int x, y;
    glfwGetWindowSize(glfwWindow, &x, &y);

    return Dimensions(x, y);;
}

void GLWindow::SetPosition(const ScreenPoint& newPosition) {
    glfwSetWindowPos(glfwWindow, newPosition.x, newPosition.y);
}

void GLWindow::SetDimensions(const ScreenDimensions& newDimensions) {
    glfwSetWindowSize(glfwWindow, newDimensions.x, newDimensions.y);
}

void GLWindow::PollSystemEvents() {
    glfwPollEvents();
}
}
} // namespace glove