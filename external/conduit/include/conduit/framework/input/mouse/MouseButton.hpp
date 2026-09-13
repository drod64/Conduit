#ifndef CONDUIT_MOUSE_BUTTON_HPP
#define CONDUIT_MOUSE_BUTTON_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
enum class MouseButton : uint16 {
    LEFT,
    RIGHT,
    MIDDLE,

    EXTRA_1,
    EXTRA_2,
    EXTRA_3,
    EXTRA_4,
    EXTRA_5
}; // enum class MouseButton
} // namespace conduit

#endif // CONDUIT_MOUSE_BUTTON_HPP