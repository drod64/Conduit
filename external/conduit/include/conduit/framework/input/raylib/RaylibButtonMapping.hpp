#ifndef CONDUIT_RAYLIB_BUTTON_MAPPING_HPP
#define CONDUIT_RAYLIB_BUTTON_MAPPING_HPP
#include <raylib.h>
#include <conduit/framework/input/keyboard/Key.hpp>
#include <conduit/framework/input/mouse/MouseButton.hpp>
#include <conduit/framework/input/gamepad/GamepadButton.hpp>

using raylibKeyButton = KeyboardKey;
using raylibMouseButton = MouseButton;
using raylibGamepadButton = GamepadButton;

namespace conduit::raylib {
    raylibKeyButton toRaylibKeyButton(conduit::Key key);

    raylibMouseButton toRaylibMouseButton(conduit::MouseButton mouse_button);

    raylibGamepadButton toRaylibGamepadButton(conduit::GamepadButton gamepad_button);
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_BUTTON_MAPPING_HPP