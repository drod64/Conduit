#ifndef CONDUIT_INPUT_HPP
#define CONDUIT_INPUT_HPP
#include <raylib.h>
#include <conduit/core/config.hpp>
#include <conduit/framework/helpers/KeyboardState.hpp>
#include <conduit/framework/helpers/MouseState.hpp>
#include <conduit/framework/GamepadInput.hpp>

namespace conduit {
class Input {
private:
    KeyboardState                               m_keyboard_state;
    MouseState                                  m_mouse_state;
    GamepadInput                                m_gamepads;

    void pollKeyboard();

    void pollMouse();

    void pollGamepads();

public:
    Input() = default;
    ~Input() = default;

    /**
     * Polls the input for the current frame
     */
    void poll();

    /**
     * @return the state of the keyboard for the current frame
     */
    const KeyboardState& keyboard() const;

    /**
     * @return the state of the mouse for the current frame
     */
    const MouseState& mouse() const;

    /**
     * @return the state of the gamepads for the current frame
     */
    const GamepadInput& gamepads() const;
}; // class Input
} // namespace conduit

#endif // CONDUIT_INPUT_HPP