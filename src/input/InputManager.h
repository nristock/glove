#ifndef INPUT_INPUTMANAGER_H_
#define INPUT_INPUTMANAGER_H_

#include "core/GloveCore.h"
#include "core/GloveObject.h"
#include "event/EventBus.h"
#include "event/EventSubscriber.h"
#include "event/type/KeyEvent.h"

namespace glove {

enum KeyState {
	/** The key is up */
	KS_UP,
	/** The key is down */
	KS_DOWN,
	/** The key has just been pushed down */
	KS_PRESSED,
	/** The key has just been released */
	KS_RELEASED
};

class InputManager : public GloveObject, public EventSubscriber, public std::enable_shared_from_this < InputManager > {
	GLOVE_MEM_ALLOC_FUNCS("InputManager")
public:
	InputManager();
	virtual ~InputManager();

	virtual void OnKeyEvent(const KeyEvent& evnt);

	virtual void SyncUpdate();

	virtual const KeyState& GetKey(const KeyCode& key) const { return keyMap[key]; }
	virtual bool IsKeyDown(const KeyCode& key) const { return GetKey(key) == KS_DOWN; }
	virtual bool IsKeyPressed(const KeyCode& key) const { return GetKey(key) == KS_PRESSED; }
	virtual bool IsKeyReleased(const KeyCode& key) const { return GetKey(key) == KS_RELEASED; }

private:
	KeyState keyMap[KC_LAST];
};


} // namespace glove

#endif