#ifndef CONDUIT_RAYLIB_GAMEPAD_INPUT_HPP
#define CONDUIT_RAYLIB_GAMEPAD_INPUT_HPP
#include <raylib.h>
#include <conduit/core/primitives.hpp>
#include <conduit/framework/input/raylib/RaylibInputMapping.hpp>
#include <conduit/framework/input/gamepad/GamepadButton.hpp>
#include <conduit/framework/input/gamepad/GamepadStates.hpp>

namespace conduit::raylib {
class RaylibGamepadInput {
private:

    void pollConnection(int gamepad, GamepadState &state);
    void pollAxes(int gamepad, GamepadState &state);
    void pollButtons(int gamepad, GamepadState &state);

public:
    RaylibGamepadInput() = default;
    ~RaylibGamepadInput() = default;

    void poll(GamepadStates &gamepad_states);
}; // class RaylibGamepadInput
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_GAMEPAD_INPUT_HPP