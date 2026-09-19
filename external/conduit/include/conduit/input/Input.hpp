#ifndef CONDUIT_INPUT_HPP
#define CONDUIT_INPUT_HPP
#include <conduit/core/config.hpp>
#include <conduit/input/keyboard/KeyboardState.hpp>
#include <conduit/input/mouse/MouseState.hpp>
#include <conduit/input/gamepad/GamepadStates.hpp>

namespace conduit {
// Forward
namespace glfw{
    class GLFWInput;
} // namespace conduit::glfw

/**
 * State tracker of all supported input sources (keyboard, mouse, gamepads).
 */
class Input {
private:
    KeyboardState                               m_keyboard_state{};
    MouseState                                  m_mouse_state{};
    GamepadStates                               m_gamepad_states{};

public:
    friend class glfw::GLFWInput;
    Input() = default;
    ~Input() = default;

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
    const GamepadStates& gamepads() const;
}; // class Input
} // namespace conduit

#endif // CONDUIT_INPUT_HPP