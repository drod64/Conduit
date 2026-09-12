#ifndef CONDUIT_INPUT_HPP
#define CONDUIT_INPUT_HPP
#include <raylib.h>
#include <conduit/framework/helpers/KeyboardState.hpp>
#include <conduit/framework/helpers/MouseState.hpp>
#include <conduit/framework/helpers/GamepadState.hpp>

namespace conduit {
class Input {
private:
    KeyboardState                               m_keyboard_states;
    MouseState                                  m_mouse_states;
    GamepadState                                m_gamepad_states;

    /**
     * Updates the physical states of the input sources for the current frame
     */
    void updatePhysicalStates();

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
     * @return the state of the gamepad for the current frame
     */
    const GamepadState& gamepad() const;
}; // class Input
} // namespace conduit

#endif // CONDUIT_INPUT_HPP