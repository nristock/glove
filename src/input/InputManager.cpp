#include "InputManager.h"

#include <boost/format.hpp>

namespace glove {
	
InputManager::InputManager() {
	for (int i = 0; i < KC_LAST; i++) {
		keyMap[i] = KS_UP;
	}
}

InputManager::~InputManager() {	
}

void InputManager::OnKeyEvent(const KeyEvent& evnt) {
	if (evnt.keyCode >= KC_LAST) {
		OLOG(error, (boost::format("KeyCode %1% of event is out of %2% range") % evnt.keyCode % KC_LAST).str());
		return;
	}
	
	KeyState previousState = keyMap[evnt.keyCode];
	
	if (previousState == KS_UP && evnt.action == KA_PRESS) {
		keyMap[evnt.keyCode] = KS_PRESSED;
		return;
	}

	if (previousState == KS_DOWN && evnt.action == KA_RELEASE) {
		keyMap[evnt.keyCode] = KS_RELEASED;
		return;
	}

	if (evnt.action == KA_PRESS) {
		keyMap[evnt.keyCode] = KS_DOWN;
		return;
	}

	if (evnt.action == KA_RELEASE) {
		keyMap[evnt.keyCode] = KS_UP;
		return;
	}
}

void InputManager::SyncUpdate() {
	for (int i = 0; i < KC_LAST; i++) {
		if (keyMap[i] == KS_PRESSED) {
			keyMap[i] = KS_DOWN;
		}
		else if (keyMap[i] == KS_RELEASED) {
			keyMap[i] = KS_UP;
		}
	}
}

} // namespace glove