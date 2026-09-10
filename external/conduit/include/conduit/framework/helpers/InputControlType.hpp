#ifndef INPUT_CONTROL_TYPE_HPP
#define INPUT_CONTROL_TYPE_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
enum class InputControlType : uint16 {
    BUTTON,
    AXIS
}; // enum class InputControlType
} // namespace conduit

#endif // INPUT_CONTROL_TYPE_HPP