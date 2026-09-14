#ifndef CONDUIT_KEYBOARD_STATE_HPP
#define CONDUIT_KEYBOARD_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/framework/input/keyboard/Key.hpp>
#include <conduit/core/containers/bitset.hpp>

namespace conduit {
struct KeyboardState {
    bitset<static_cast<sizet>(Key::MAX_COUNT)> current;
    bitset<static_cast<sizet>(Key::MAX_COUNT)> previous;
}; // struct KeyboardState
} // namespace conduit

#endif // CONDUIT_KEYBOARD_STATE_HPP