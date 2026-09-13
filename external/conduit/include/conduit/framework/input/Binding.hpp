#ifndef CONDUIT_BINDING_HPP
#define CONDUIT_BINDING_HPP
#include <conduit/framework/input/InputDevice.hpp>
#include <conduit/framework/input/InputControlType.hpp>

namespace conduit {
struct Binding {

    Binding(uint16 control, InputDevice device, InputControlType type) :
    control(control),
    device(device),
    type(type)
    {}
    
    uint16              control;
    InputDevice         device;
    InputControlType    type;
}; // struct Binding
} // namespace conduit

#endif // CONDUIT_BINDING_HPP