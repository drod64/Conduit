#ifndef CONDUIT_BINDING_HPP
#define CONDUIT_BINDING_HPP
#include <conduit/framework/helpers/InputDevice.hpp>
#include <conduit/framework/helpers/InputControlType.hpp>

namespace conduit {
struct Binding {
    InputDevice         device;
    InputControlType    type;
    uint16              control;
}; // struct Binding
} // namespace conduit

#endif // CONDUIT_BINDING_HPP