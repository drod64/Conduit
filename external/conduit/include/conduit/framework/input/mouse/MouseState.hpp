#ifndef CONDUIT_MOUSE_STATE_HPP
#define CONDUIT_MOUSE_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/bitset.hpp>
#include <conduit/framework/input/mouse/MouseButton.hpp>
#include <sm/Vec2.h>

namespace conduit {
struct MouseState {
    bitset<static_cast<sizet>(MouseButton::MAX_COUNT)> current;
    bitset<static_cast<sizet>(MouseButton::MAX_COUNT)> previous;

    sm::Vec2 position;
    sm::Vec2 delta;
    sm::Vec2 wheel;
}; // struct MouseState
} // namespace conduit

#endif // CONDUIT_MOUSE_STATE_HPP