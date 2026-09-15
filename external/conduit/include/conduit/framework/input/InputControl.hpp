#ifndef INPUT_CONTROL_HPP
#define INPUT_CONTROL_HPP
#include <conduit/core/containers/variant.hpp>
#include <conduit/framework/input/InputTypes.hpp>

namespace conduit {
using InputControl = variant <
    GamepadAxis,
    GamepadButton,
    Key,
    MouseButton >;
} // namespace conduit

#endif // INPUT_CONTROL_HPP