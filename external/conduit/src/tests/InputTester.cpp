#include <conduit/tests/InputTester.hpp>

void conduit::InputTester::test()
{
    conduit::ActionMap<Action> actions(m_input);

    // Create bindings.
    conduit::Binding forward_wasd(Key::W, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding forward_keys(Key::UP, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding left_wasd(Key::A, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding left_keys(Key::LEFT, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding backward_wasd(Key::S, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding backward_keys(Key::DOWN, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding right_wasd(Key::D, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding right_keys(Key::RIGHT, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding jump(Key::SPACE, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding quit(Key::Q, InputDevice::KEYBOARD, InputControlType::BUTTON);

    // Bind actions to bindings.
    actions.bind(Action::FORWARD, forward_wasd);
    actions.bind(Action::FORWARD, forward_keys);
    actions.bind(Action::LEFT, left_wasd);
    actions.bind(Action::LEFT, left_keys);
    actions.bind(Action::BACKWARD, backward_wasd);
    actions.bind(Action::BACKWARD, backward_keys);
    actions.bind(Action::RIGHT, right_wasd);
    actions.bind(Action::RIGHT, right_keys);
    actions.bind(Action::JUMP, jump);
    actions.bind(Action::QUIT, quit);

    // Initialize window
    InitWindow(100, 100, "Conduit");
    SetTargetFPS(conduit::config::TARGET_FRAME_RATE);

    // Simple loop to poll input
    while (!WindowShouldClose())
    {
        PollInputEvents();

        // Poll hardware.
        m_raylib_input.poll(m_input);
        
        // Poll actions.
        actions.poll();

        if (actions.isDown(Action::FORWARD))
        {
            std::cout << "Moving forward\n";
        }
        
        if (actions.isDown(Action::BACKWARD))
        {
            std::cout << "Moving backward\n";
        }

        if (actions.isDown(Action::LEFT))
        {
            std::cout << "Moving left\n";
        }
        
        if (actions.isDown(Action::RIGHT))
        {
            std::cout << "Moving right\n";
        }

        if (actions.wasPressed(Action::JUMP))
        {
            std::cout << "Jumped\n";
        }

        if (actions.wasReleased(Action::QUIT))
        {
            CloseWindow();
        }
    }
}