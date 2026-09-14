#ifndef CONDUIT_GAMEPAD_STATE_HPP
#define CONDUIT_GAMEPAD_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/array.hpp>
#include <conduit/core/containers/bitset.hpp>
#include <conduit/framework/input/gamepad/GamepadButton.hpp>
#include <conduit/framework/input/gamepad/GamepadAxis.hpp>

namespace conduit {
struct GamepadState {
    bool connected = false;
    bitset<static_cast<sizet>(GamepadButton::MAX_COUNT)> current{};
    bitset<static_cast<sizet>(GamepadButton::MAX_COUNT)> previous{};
    array<real, static_cast<sizet>(GamepadAxis::MAX_COUNT)> axes{};
}; // struct GamepadState
} // namespace conduit

#endif // CONDUIT_GAMEPAD_STATE_HPP