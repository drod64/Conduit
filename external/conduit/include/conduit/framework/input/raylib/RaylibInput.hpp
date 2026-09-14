#ifndef CONDUIT_RAYLIB_INPUT_HPP
#define CONDUIT_RAYLIB_INPUT_HPP
#include <conduit/framework/input/Input.hpp>
#include <conduit/framework/input/raylib/RaylibInputMapping.hpp>
#include <conduit/framework/input/raylib/RaylibGamepadInput.hpp>

namespace conduit::raylib {
class RaylibInput {
private:
    RaylibGamepadInput m_gamepad_input;

    void pollKeyboard(KeyboardState &keyboard_state);

    void pollMouse(MouseState &mouse_state);

    void pollGamepads(GamepadStates &gamepad_states);

public:
    RaylibInput() = default;
    ~RaylibInput() = default;

    void poll(Input &input);
}; // class RaylibInput
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_INPUT_HPP