#pragma once

#include <glm/glm.hpp>

#include "glove/log/Log.hpp"
#include "glove/GloveCore.hpp"
#include "glove/events/EventBus.hpp"
#include "glove/events/type/KeyEvent.hpp"
#include "glove/events/type/MouseButtonEvent.hpp"
#include "glove/events/type/MouseMoveEvent.hpp"

namespace glove {

enum GLOVE_API_EXPORT KeyState {
    /** The key is up */
    KS_UP,
    /** The key is down */
    KS_DOWN,
    /** The key has just been pushed down */
    KS_PRESSED,
    /** The key has just been released */
    KS_RELEASED
};

enum GLOVE_API_EXPORT ButtonState {
    /** The key is up */
    BS_UP,
    /** The key is down */
    BS_DOWN,
    /** The key has just been pushed down */
    BS_PRESSED,
    /** The key has just been released */
    BS_RELEASED
};

class GLOVE_API_EXPORT InputManager : public std::enable_shared_from_this<InputManager> {
    public : InputManager(EventBusPtr& eventBus);

    virtual ~InputManager();

    virtual void OnKeyEvent(const KeyEvent& evnt);

    virtual void OnMouseButtonEvent(const MouseButtonEvent& evnt);

    virtual void OnMouseMoveEvent(const MouseMoveEvent& evnt);

    virtual void SyncUpdate();

    virtual const KeyState& GetKey(const KeyCode& key) const { return keyMap[key]; }

    virtual bool IsKeyDown(const KeyCode& key) const { return GetKey(key) == KS_DOWN; }

    virtual bool IsKeyPressed(const KeyCode& key) const { return GetKey(key) == KS_PRESSED; }

    virtual bool IsKeyReleased(const KeyCode& key) const { return GetKey(key) == KS_RELEASED; }

    virtual const ButtonState& GetButton(const MouseButton& button) const { return mouseButtonMap[button]; }

    virtual bool IsButtonDown(const MouseButton& button) const { return GetButton(button) == BS_DOWN; }

    virtual bool IsButtonPressed(const MouseButton& button) const { return GetButton(button) == BS_PRESSED; }

    virtual bool IsButtonyReleased(const MouseButton& button) const { return GetButton(button) == BS_RELEASED; }

    virtual glm::vec2 GetMousePosition() const { return mousePosition; }

    virtual const glm::vec2& GetMousePositionRef() const { return mousePosition; }

  private:
    logging::GloveLogger logger;

    KeyState keyMap[KC_LAST];
    ButtonState mouseButtonMap[MB_LAST];

    glm::vec2 mousePosition;
};

} // namespace glove