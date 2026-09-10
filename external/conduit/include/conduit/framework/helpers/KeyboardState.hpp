#ifndef CONDUIT_KEYBOARD_STATE_HPP
#define CONDUIT_KEYBOARD_STATE_HPP
#include <conduit/core/config.hpp>
#include <conduit/core/containers/bitset.hpp>

namespace conduit {
struct KeyboardState {
    bitset<config::KEYBOARD_KEY_COUNT> current;
    bitset<config::KEYBOARD_KEY_COUNT> previous;
}; // struct KeyboardState
} // namespace conduit

#endif // CONDUIT_KEYBOARD_STATE_HPP