#ifndef CONDUIT_INPUT_HPP
#define CONDUIT_INPUT_HPP
#include <conduit/core/containers/unordered_map.hpp>
#include <conduit/core/containers/vector.hpp>
#include <conduit/framework/helpers/ActionState.hpp>
#include <conduit/framework/helpers/Binding.hpp>
#include <conduit/framework/helpers/KeyboardState.hpp>
#include <conduit/framework/helpers/MouseState.hpp>
#include <conduit/framework/helpers/GamepadState.hpp>

namespace conduit {
template <typename Action>
class Input {
private:
    unordered_map<Action, vector<Binding>>      m_bindings;
    unordered_map<Action, ActionState>          m_action_states;
    KeyboardState                               m_keyboard_states;
    MouseState                                  m_mouse_states;
    GamepadState                                m_gamepad_states;

    bool buttonDown(const Binding &binding) const;
    real axisValue(const Binding &binding) const;
    void updatePhysicalStates();
    void updateActionStates();

public:
    Input() = default;
    ~Input() = default;

    void poll();
    bool isDown(Action action) const;
    bool wasPressed(Action action) const;
    bool wasReleased(Action action) const;
    real value(Action action) const;

    void bind(Action action, const Binding &binding);
    void unbind(Action action, const Binding &binding);
}; // class Input
} // namespace conduit

// Implementation

template <typename Action>
void conduit::Input<Action>::poll()
{
    // TODO
}

template <typename Action>
bool conduit::Input<Action>::isDown(Action action) const
{
    return m_action_states[action].down;
}

template <typename Action>
bool conduit::Input<Action>::wasPressed(Action action) const
{
    return m_action_states[action].pressed;
}

template <typename Action>
bool conduit::Input<Action>::wasReleased(Action action) const
{
    return m_action_states[action].released;
}

template <typename Action>
conduit::real conduit::Input<Action>::value(Action action) const
{
    return m_action_states[action].value;
}

template <typename Action>
void conduit::Input<Action>::bind(Action action, const Binding &binding)
{
    // TODO
}

template <typename Action>
void conduit::Input<Action>::unbind(Action action, const Binding &binding)
{
    // TODO
}

#endif // CONDUIT_INPUT_HPP