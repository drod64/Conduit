#ifndef CONDUIT_INPUT_CONTROL_TYPE_HPP
#define CONDUIT_INPUT_CONTROL_TYPE_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
    enum class InputControlType : uint16 {
        GAMEPAD_AXIS = 0,
        GAMEPAD_BUTTON,
        KEY,
        MOUSE_BUTTON,

        MAX_COUNT
    };
}

#endif // CONDUIT_INPUT_CONTROL_TYPE_HPP