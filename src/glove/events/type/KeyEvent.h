#pragma once

#include "glove/events/AbstractEvent.h"

namespace glove {

/** Key code enum - values are mostly take from GLFW mappings */
enum KeyCode {
    KC_UNKNOWN = 0,

    KC_SPACE = 32,
    KC_APOSTROPHE = 36, /* ' */

    KC_COMMA = 44,
    KC_MINUS,
    KC_PERIOD,
    KC_SLASH = 47,

    /** Numerical keys */
    KC_0 = 48,
    KC_1,
    KC_2,
    KC_3,
    KC_4,
    KC_5,
    KC_6,
    KC_7,
    KC_8,
    KC_9 = 57,

    KC_SEMICOLON = 59,
    KC_EQUAL = 61,

    /** Alpha keys */
    KC_A = 65,
    KC_B,
    KC_C,
    KC_D,
    KC_E,
    KC_F,
    KC_G,
    KG_H,
    KC_I,
    KC_J,
    KC_K,
    KC_L,
    KC_M,
    KC_N,
    KC_O,
    KC_P = 80,
    KC_Q,
    KC_R,
    KC_S,
    KC_T,
    KC_U,
    KC_V,
    KC_W,
    KC_X,
    KC_Y,
    KC_Z = 90,

    KC_LEFT_BRACKET = 91,  /* [ */
    KC_BACKSLASH = 92,     /* \ */
    KC_RIGHT_BRACKET = 93, /* ] */
    KC_GRAVE = 96,         /* ` */
    KC_INTERNAT_1 = 161,
    KC_INTERNAT_2 = 162,

    /** Special keys */
    KC_ESCAPE = 256,
    KC_ENTER,
    KC_TAB,
    KC_BACKSPACE,
    KC_INSERT,
    KC_DELETE,
    KC_RIGHT = 262,
    KC_LEFT,
    KC_DOWN,
    KC_UP,
    KC_PAGE_UP,
    KC_PAGE_DOWN,
    KC_HOME,
    KC_END = 269,

    /** Lock keys */
    KC_CAPS_LOCK = 280,
    KC_SCROLL_LOCK,
    KC_NUM_LOCK,
    KC_PRINT_SCREEN,
    KC_PAUSE = 284,

    /** F-Keys */
    KC_F1 = 290,
    KC_F2,
    KC_F3,
    KC_F4,
    KC_F5,
    KC_F6,
    KC_F7,
    KC_F8,
    KC_F9,
    KC_F10 = 299,
    KC_F11,
    KC_F12,
    KC_F13,
    KC_F14,
    KC_F15,
    KC_F16,
    KC_F17,
    KC_F18,
    KC_F19,
    KC_F20 = 309,
    KC_F21,
    KC_F22,
    KC_F23,
    KC_F24,
    KC_F25 = 314,

    /** Keypad keys */
    KC_NUM_0 = 320,
    KC_NUM_1,
    KC_NUM_2,
    KC_NUM_3,
    KC_NUM_4,
    KC_NUM_5,
    KC_NUM_6,
    KC_NUM_7,
    KC_NUM_8,
    KC_NUM_9 = 329,
    KC_NUM_DECIMAL,
    KC_NUM_DIVIDE,
    KC_NUM_MULTIPLY,
    KC_NUM_SUBTRACT,
    KC_NUM_ADD,
    KC_NUM_ENTER,
    KC_NUM_EQUAL = 336,

    /** Modifier keys */
    KC_LEFT_SHIFT = 340,
    KC_LEFT_CONTROL,
    KC_LEFT_ALT,
    KC_LEFT_OS = 343,

    KC_RIGHT_SHIFT = 344,
    KC_RIGHT_CONTROL,
    KC_RIGHT_ALT,
    KC_RIGHT_OS = 347,

    KC_MENU = 348,

    KC_LAST = KC_MENU
};

enum KeyAction { KA_PRESS, KA_RELEASE, KA_REPEAT };

struct KeyEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    KeyEvent(KeyCode keyCode, KeyAction action);
    KeyEvent(KeyCode keyCode, KeyAction action, bool shiftDown, bool controlDown, bool altDown, bool osKeyDown);

    virtual ~KeyEvent();

    virtual GLOVE_INLINE const EventTypeId& GetEventType() const;

    KeyCode keyCode;
    KeyAction action;

    bool shiftDown;
    bool controlDown;
    bool altDown;
    bool osKeyDown;
};

} // namespace glove