#include "../../Headers/Events/KeyEvent.h"

KEY KeyEvent::getKey() const {
    return _pressedKey;
}

KeyEvent::KeyEvent(KEY pressedKey, KeyEventType eventType) : _pressedKey(pressedKey), _eventType(eventType) {

}

KeyEventType KeyEvent::getKeyEventType() const {
    return _eventType;
}
