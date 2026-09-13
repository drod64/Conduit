#ifndef CONDUIT_MOUSE_AXIS_HPP
#define CONDUIT_MOUSE_AXIS_HPP

namespace conduit {
enum class MouseAxis {
    POSITION_X,
    POSITION_Y,

    DELTA_X,
    DELTA_Y,

    WHEEL_X,
    WHEEL_Y
}; // enum class MouseAxis
} // namespace conduit

#endif // CONDUIT_MOUSE_AXIS_HPP