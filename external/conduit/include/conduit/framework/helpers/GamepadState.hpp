#ifndef CONDUIT_GAMEPAD_STATE_HPP
#define CONDUIT_GAMEPAD_STATE_HPP
#include <conduit/core/config.hpp>
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/array.hpp>
#include <conduit/core/containers/bitset.hpp>

namespace conduit {
struct GamepadState {
    bool connected = false;
    bitset<config::GAMEPAD_BUTTON_COUNT> current;
    bitset<config::GAMEPAD_BUTTON_COUNT> previous;
    array<real, config::GAMEPAD_AXIS_COUNT> axes;
}; // struct GamepadState
} // namespace conduit

#endif // CONDUIT_GAMEPAD_STATE_HPP