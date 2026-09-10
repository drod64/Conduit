#ifndef CONDUIT_MOUSE_STATE_HPP
#define CONDUIT_MOUSE_STATE_HPP
#include <conduit/core/config.hpp>
#include <conduit/core/containers/bitset.hpp>
#include <sm/Vec2.h>

namespace conduit {
struct MouseState {
    bitset<config::MOUSE_BUTTON_COUNT> current;
    bitset<config::MOUSE_BUTTON_COUNT> previous;

    sm::Vec2 position;
    sm::Vec2 delta;
    sm::Vec2 wheel;
}; // struct MouseState
} // namespace conduit

#endif // CONDUIT_MOUSE_STATE_HPP