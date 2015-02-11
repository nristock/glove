#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/format.hpp>

#include <glove/rendering/WindowConstructionHints.hpp>
#include <glove/events/type/KeyEvent.hpp>
#include <glove/events/type/MouseMoveEvent.hpp>
#include <glove/events/type/MouseButtonEvent.hpp>
#include <glove/events/EventBus.hpp>

#include "GLWindow.hpp"
#include "internal/GlfwWrapper.hpp"

namespace {

bool inline IsModifierKeyDown(int modsFlag, int keyToCheck) {
    return (modsFlag & keyToCheck) != 0;
}

bool inline IsAltKeyDown(int modsFlag) {
    return IsModifierKeyDown(modsFlag, GLFW_MOD_ALT);
}

bool inline IsCtrlKeyDown(int modsFlag) {
    return IsModifierKeyDown(modsFlag, GLFW_MOD_CONTROL);
}

bool inline IsShiftKeyDown(int modsFlag) {
    return IsModifierKeyDown(modsFlag, GLFW_MOD_SHIFT);
}

bool inline IsSuperKeyDown(int modsFlag) {
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

ScreenDimensions GLWindow::GetDimensions() const {
    int x, y;
    glfwGetWindowSize(glfwWindow, &x, &y);

    return ScreenDimensions(x, y);
}

void GLWindow::SetPosition(const ScreenPoint& newPosition) {
    glfwSetWindowPos(glfwWindow, newPosition.x, newPosition.y);
}

void GLWindow::SetDimensions(const ScreenDimensions& newDimensions) {
    glfwSetWindowSize(glfwWindow, static_cast<int>(newDimensions.GetWidth()), static_cast<int>(newDimensions.GetHeight()));
}

void GLWindow::PollSystemEvents() {
    glfwPollEvents();
}
}
} // namespace glove