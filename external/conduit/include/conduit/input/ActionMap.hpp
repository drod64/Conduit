#ifndef CONDUIT_ACTION_MAP_HPP
#define CONDUIT_ACTION_MAP_HPP
#include <cassert>
#include <cstdlib>
#include <conduit/core/containers/unordered_map.hpp>
#include <conduit/core/containers/vector.hpp>
#include <conduit/input/ActionEntry.hpp>
#include <conduit/input/Input.hpp>

namespace conduit {
/**
 * Logical action tracker that allows multiple bindings to affect one action.
 */
template <typename Action>
class ActionMap {
private:
    const Input&                                m_input;
    sizet                                       m_gamepad{};
    unordered_map<Action, sizet>                m_action_to_id{};
    unordered_map<sizet, Action>                m_id_to_action{};
    vector<ActionEntry>                         m_action_entries{};

    /**
     * Helper function that evaluates a binding.
     * 
     * @param binding the binding to evaluate
     * 
     * @return the value of the binding
     */
    real evaluate(const Binding &binding) const;

    /**
     * Helper function that evaluates a GamepadAxis.
     * 
     * @param gamepadAxis the gamepad axis to query
     * 
     * @return the value of the gamepad axis
     */
    real evaluate(GamepadAxis gamepadAxis) const;
    
    /**
     * Helper function that evaluates a GamepadButton.
     * 
     * @param gamepadButton the gamepad button to query
     * 
     * @return the value of the gamepad button
     */
    real evaluate(GamepadButton gamepadButton) const;

    /**
     * Helper function that evaluates a Key.
     * 
     * @param key the key to query
     * 
     * @return the value of the key
     */
    real evaluate(Key key) const;

    /**
     * Helper function that evaluates a MouseButton.
     * 
     * @param mouseButton the mouse button to query
     * 
     * @return the value of the mouse button
     */
    real evaluate(MouseButton mouseButton) const;

public:
    /**
     * Parameterized constructor.
     * 
     * @param input a required input source to read states from
     * @param gamepad an optional index to query a specific gamepad
     */
    ActionMap(const Input &input, sizet gamepad = 0);
    ~ActionMap() = default;

    /**
     * Polls the stored conduit::Input to update the action states.
     */
    void poll();

    /**
     * @param action the action to check
     * 
     * @return true if a binding linked to the action is down, false otherwise
     */
    bool isDown(Action action) const;

    /**
     * @param action the action to check
     * 
     * @return true if a binding linked to the action was pressed, false otherwise
     */
    bool wasPressed(Action action) const;

    /**
     * @param action the action to check
     * 
     * @return true if a binding linked to the action was released, false otherwise
     */
    bool wasReleased(Action action) const;

    /**
     * @param action the action to query
     * 
     * @return the raw value of the action (useful for analog cases)
     */
    real value(Action action) const;

    /**
     * Binds a specified binding to an action.
     * 
     * @param action the action
     * @param binding the binding linked to the action
     */
    void bind(Action action, const Binding &binding);

    /**
     * Binds a specified binding to an action.
     * 
     * @param action the action
     * @param inputControl the control linked to the action
     * @param scale optional scale that is multiplied to the action's raw value (defaulted to 1)
     */
    void bind(Action action, InputControl inputControl, real scale = static_cast<real>(1));

    /**
     * Unbinds a specified binding from an action.
     * 
     * @param action the action
     * @param binding the binding to unlink/unbind
     */
    void unbind(Action action, const Binding &binding);
}; // class ActionMap<Action>
} // namespace conduit

// Implementation
template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(const Binding &binding) const
{
    uint32 binding_value = binding.control.value();

    real value = 0;

    switch (binding.control.type())
    {
        case InputControlType::GAMEPAD_AXIS:
            value = evaluate(static_cast<GamepadAxis>(binding_value));
            break;
        
        case InputControlType::GAMEPAD_BUTTON:
            value = evaluate(static_cast<GamepadButton>(binding_value));
            break;

        case InputControlType::KEY:
            value = evaluate(static_cast<Key>(binding_value));
            break;

        case InputControlType::MOUSE_BUTTON:
            value = evaluate(static_cast<MouseButton>(binding_value));
            break;

        default:
            value = 0;
            break;
    }

    return value * binding.scale;
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(GamepadAxis gamepadAxis) const
{
    return m_input.gamepads()[m_gamepad].axisValue(gamepadAxis);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(GamepadButton gamepadButton) const
{
    return (m_input.gamepads()[m_gamepad].isDown(gamepadButton)) ?
            static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(Key key) const
{
    return (m_input.keyboard().isDown(key)) ?
        static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(MouseButton mouseButton) const
{
    return (m_input.mouse().isDown(mouseButton)) ?
        static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
inline conduit::ActionMap<Action>::ActionMap(const Input &input, sizet gamepad) :
m_input(input),
m_gamepad(gamepad)
{}

template <typename Action>
inline void conduit::ActionMap<Action>::poll()
{
    for (ActionEntry &action_entry : m_action_entries)
    {
        ActionState &action_state = action_entry.state;

        action_state.previous = action_state.current;
        action_state.current = static_cast<real>(0);

        for (const Binding &binding : action_entry.bindings)
        {
            action_state.current += evaluate(binding);
        }

        action_state.current = std::clamp(action_state.current, static_cast<real>(-1), static_cast<real>(1));
    }
}

template <typename Action>
inline bool conduit::ActionMap<Action>::isDown(Action action) const
{
    auto it = m_action_to_id.find(action);

    if (it != m_action_to_id.end())
    {
        const sizet ID = *it;

        const ActionEntry& entry = m_action_entries[ID];

        return entry.state.current != 0;
    }

    return false;
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasPressed(Action action) const
{
    auto it = m_action_to_id.find(action);

    if (it != m_action_to_id.end())
    {
        const sizet ID = it->second;

        const ActionEntry& entry = m_action_entries.at(ID);

        return entry.state.previous == 0 && entry.state.current != 0;
    }

    return false;
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasReleased(Action action) const
{
    auto it = m_action_to_id.find(action);

    if (it != m_action_to_id.end())
    {
        const sizet ID = it->second;

        const ActionEntry& entry = m_action_entries.at(ID);

        return entry.state.previous != 0 && entry.state.current == 0;
    }

    return false;
}

template <typename Action>
inline conduit::real conduit::ActionMap<Action>::value(Action action) const
{
    auto it = m_action_to_id.find(action);

    if (it != m_action_to_id.end())
    {
        const sizet ID = it->second;

        const ActionEntry& entry = m_action_entries.at(ID);

        return entry.state.current;
    }

    return 0;
}

template <typename Action>
void conduit::ActionMap<Action>::bind(Action action, const Binding &binding)
{
    auto it = m_action_to_id.find(action);
    
    if (it == m_action_to_id.end())
    {
        const sizet ID = m_action_entries.size();
        m_action_to_id[action]  = ID;
        m_id_to_action[ID]      = action;
        m_action_entries.push_back(ActionEntry());
    }

    const sizet ID = m_action_to_id[action];
    m_action_entries[ID].bindings.push_back(binding);
}

template <typename Action>
void conduit::ActionMap<Action>::bind(Action action, InputControl inputControl, real scale)
{
    bind(action, Binding(inputControl, scale));
}

template <typename Action>
void conduit::ActionMap<Action>::unbind(Action action, const Binding &binding)
{
    auto it = m_action_to_id.find(action);

    if (it == m_action_to_id.end()) return;

    const size_t TARGET_ID = it->second;
    auto& entry = m_action_entries[TARGET_ID];

    // Remove the requested binding.
    auto bindingIt = std::find(entry.bindings.begin(), entry.bindings.end(), entry.bindings);

    if (bindingIt == entry.bindings.end()) return;

    *bindingIt = std::move(entry.bindings.back());
    entry.bindings.pop_back();

    // Keep the action if it still has bindings.
    if (!entry.bindings.empty()) return;

    // Action has no bindings left, so remove the action itself.
    const size_t LAST_ID = m_action_entries.size() - 1;

    if (TARGET_ID != LAST_ID)
    {
        m_action_entries[TARGET_ID] = std::move(m_action_entries[LAST_ID]);

        const Action movedAction = m_id_to_action[LAST_ID];

        m_id_to_action[TARGET_ID] = movedAction;
        m_action_to_id[movedAction] = TARGET_ID;
    }

    m_action_entries.pop_back();
    m_id_to_action.erase(LAST_ID);
    m_action_to_id.erase(action);
}

#endif // CONDUIT_ACTION_MAP_HPP