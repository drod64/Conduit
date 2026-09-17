#ifndef CONDUIT_KEYBOARD_STATE_HPP
#define CONDUIT_KEYBOARD_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/framework/input/keyboard/Key.hpp>
#include <conduit/core/containers/bitset.hpp>

namespace conduit {
class KeyboardState {
private:
    bitset<static_cast<sizet>(Key::MAX_COUNT)> m_current{};
    bitset<static_cast<sizet>(Key::MAX_COUNT)> m_previous{};

public:
    KeyboardState() = default;
    ~KeyboardState() = default;

    bool isDown(Key key) const;
    bool wasPressed(Key key) const;
    bool wasReleased(Key key) const;
    
    void reset();
    void setKey(Key key, bool state);
    void updatePrevious();
}; // class KeyboardState
} // namespace conduit

#endif // CONDUIT_KEYBOARD_STATE_HPP