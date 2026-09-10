#ifndef CONDUIT_INPUT_DEVICE_HPP
#define CONDUIT_INPUT_DEVICE_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
enum class InputDevice : uint16 {
    KEYBOARD,
    MOUSE,
    GAMEPAD
}; // enum class InputDevice
} // namespace conduit

#endif // CONDUIT_INPUT_DEVICE_HPP