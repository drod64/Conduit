#ifndef CONDUIT_GAME_PAD_AXIS_HPP
#define CONDUIT_GAME_PAD_AXIS_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
enum class GamepadAxis : uint16 {
    LEFT_STICK_X,
    LEFT_STICK_Y,
    RIGHT_STICK_X,
    RIGHT_STICK_Y,

    LEFT_TRIGGER,
    RIGHT_TRIGGER
}; 
} // namespace conduit

#endif // CONDUIT_GAME_PAD_AXIS_HPP