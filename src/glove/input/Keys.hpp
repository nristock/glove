#pragma once

#include <string>

#include "glove/GloveApi.hpp"
#include "glove/events/EventDelegate.hpp"
#include "glove/input/events/KeyStateChanged.hpp"

namespace glove {
/// \brief Immutable class representing a key's state.
class GLOVE_API_EXPORT KeyState {
  public:
    KeyState(float keyValue) : keyValue(keyValue) {
    }

    KeyState(bool isDown) : keyValue(isDown ? 0.0f : 1.0f) {
    }

    inline float GetAxisValue() const {
        return keyValue;
    }

    inline bool IsKeyDown() const {
        return keyValue == 0.0f;
    }

    inline bool IsKeyUp() const {
        return keyValue == 1.0f;
    }

  private:
    float keyValue;
};

class GLOVE_API_EXPORT Key {
  public:
    enum class Type {
        BUTTON, FLOAT_AXIS
    };

    Key(const std::string& technicalName, const Type keyType) :
            technicalName(technicalName),
            nameHash(std::hash<std::string>()(technicalName)),
            keyType(keyType),
            keyState(false) {
    }

    Key(const Key& other) = delete;
    Key(Key&& other) = delete;
    Key& operator=(const Key& other) = delete;

    bool operator==(const Key& other) const {
        return nameHash == other.nameHash && keyType == other.keyType;
    }

    bool operator!=(const Key& other) const {
        return !operator==(other);
    }

    const KeyState& GetState() const {
        return keyState;
    }

    void UpdateState(const KeyState& keyState) const {
        if(keyType == Type::BUTTON) {
            KeyStateChanged eventData(keyState.GetAxisValue());
            this->keyState = keyState;
            onStateChangedEvent.Publish(eventData);
        }
        else{
            KeyStateChanged eventData(keyState.GetAxisValue() - this->GetState().GetAxisValue());
            this->keyState = keyState;
            onStateChangedEvent.Publish(eventData);
        }
    }

    const ThreadedEvent<KeyStateChanged>& OnStateChanged() const {
        return onStateChangedEvent;
    }

    std::string ToString() const {
        return technicalName;
    }

  private:
    const std::string technicalName;
    const std::size_t nameHash;
    const Type keyType;

    mutable KeyState keyState;
    mutable ThreadedEvent<KeyStateChanged> onStateChangedEvent;
};

namespace Keys {
// Begin of generated section. DO NOT MODIFY MANUALLY!
// [GENERATE:KEYS]
extern const Key MouseX;
extern const Key MouseY;
extern const Key MouseScrollUp;
extern const Key MouseScrollDown;

extern const Key LeftMouseButton;
extern const Key RightMouseButton;
extern const Key MiddleMouseButton;

extern const Key A;
extern const Key B;
extern const Key C;
extern const Key D;
extern const Key E;
extern const Key F;
extern const Key G;
extern const Key H;
extern const Key I;
extern const Key J;
extern const Key K;
extern const Key L;
extern const Key M;
extern const Key N;
extern const Key O;
extern const Key P;
extern const Key Q;
extern const Key R;
extern const Key S;
extern const Key T;
extern const Key U;
extern const Key V;
extern const Key W;
extern const Key X;
extern const Key Y;
extern const Key Z;

extern const Key Zero;
extern const Key One;
extern const Key Two;
extern const Key Three;
extern const Key Four;
extern const Key Five;
extern const Key Six;
extern const Key Seven;
extern const Key Eight;
extern const Key Nine;

extern const Key NumPad0;
extern const Key NumPad1;
extern const Key NumPad2;
extern const Key NumPad3;
extern const Key NumPad4;
extern const Key NumPad5;
extern const Key NumPad6;
extern const Key NumPad7;
extern const Key NumPad8;
extern const Key NumPad9;

extern const Key NumLock;

extern const Key Divide;
extern const Key Multiply;
extern const Key Subtract;
extern const Key Add;

extern const Key F1;
extern const Key F2;
extern const Key F3;
extern const Key F4;
extern const Key F5;
extern const Key F6;
extern const Key F7;
extern const Key F8;
extern const Key F9;
extern const Key F10;
extern const Key F11;
extern const Key F12;

extern const Key BackSpace;
extern const Key Enter;
extern const Key Space;
extern const Key Tab;

extern const Key Escape;
extern const Key Pause;
extern const Key CapsLock;
extern const Key PageUp;
extern const Key PageDown;
extern const Key End;
extern const Key Home;
extern const Key ScrollLock;

extern const Key Left;
extern const Key Right;
extern const Key Up;
extern const Key Down;

extern const Key Insert;
extern const Key Delete;

extern const Key LeftShift;
extern const Key RightShift;

extern const Key LeftControl;
extern const Key RightControl;

extern const Key LeftAlt;
extern const Key RightAlt;

extern const Key LeftBracket;
extern const Key RightBracket;
extern const Key Backslash;

extern const Key Semicolon;
extern const Key Hyphen;

extern const Key Comma;
extern const Key Period;
extern const Key Slash;
// [\GENERATE:KEYS]
// End of generated section.
}
}