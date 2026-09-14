#ifndef CONDUIT_RAYLIB_INPUT_MAPPING_HPP
#define CONDUIT_RAYLIB_INPUT_MAPPING_HPP
#include <cassert>
#include <cstdlib>
#include <raylib.h>
#include <conduit/framework/input/keyboard/Key.hpp>
#include <conduit/framework/input/mouse/MouseButton.hpp>
#include <conduit/framework/input/gamepad/GamepadButton.hpp>
#include <conduit/framework/input/gamepad/GamepadAxis.hpp>

using raylibKeyButton = KeyboardKey;
using raylibMouseButton = MouseButton;
using raylibGamepadButton = GamepadButton;
using raylibGamepadAxis = GamepadAxis;

namespace conduit::raylib {
    raylibKeyButton toRaylibKeyButton(conduit::Key key);

    raylibMouseButton toRaylibMouseButton(conduit::MouseButton mouse_button);

    raylibGamepadButton toRaylibGamepadButton(conduit::GamepadButton gamepad_button);

    raylibGamepadAxis toRaylibGamepadAxis(conduit::GamepadAxis gamepad_axis);
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_INPUT_MAPPING_HPP