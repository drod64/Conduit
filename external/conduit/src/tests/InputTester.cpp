#include <conduit/tests/InputTester.hpp>

void conduit::InputTester::test()
{
    conduit::Input<Action> input;

    // Create bindings.
    conduit::Binding forward_wasd(KEY_W, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding forward_keys(KEY_UP, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding left_wasd(KEY_A, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding left_keys(KEY_LEFT, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding backward_wasd(KEY_S, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding backward_keys(KEY_DOWN, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding right_wasd(KEY_D, InputDevice::KEYBOARD, InputControlType::BUTTON);
    conduit::Binding right_keys(KEY_RIGHT, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding jump(KEY_SPACE, InputDevice::KEYBOARD, InputControlType::BUTTON);

    conduit::Binding quit(KEY_Q, InputDevice::KEYBOARD, InputControlType::BUTTON);

    // Bind actions to bindings.
    input.bind(Action::FORWARD, forward_wasd);
    input.bind(Action::FORWARD, forward_keys);
    input.bind(Action::LEFT, left_wasd);
    input.bind(Action::LEFT, left_keys);
    input.bind(Action::BACKWARD, backward_wasd);
    input.bind(Action::BACKWARD, backward_keys);
    input.bind(Action::RIGHT, right_wasd);
    input.bind(Action::RIGHT, right_keys);
    input.bind(Action::JUMP, jump);
    input.bind(Action::QUIT, quit);

    // Initialize window
    InitWindow(100, 100, "Conduit");
    SetTargetFPS(conduit::config::TARGET_FRAME_RATE);

    // Simple loop to poll input
    while (!WindowShouldClose())
    {
        PollInputEvents();

        input.poll();

        if (input.isDown(Action::FORWARD))
        {
            std::cout << "Moving forward\n";
        }
        
        if (input.isDown(Action::BACKWARD))
        {
            std::cout << "Moving backward\n";
        }

        if (input.isDown(Action::LEFT))
        {
            std::cout << "Moving left\n";
        }
        
        if (input.isDown(Action::RIGHT))
        {
            std::cout << "Moving right\n";
        }

        if (input.wasPressed(Action::JUMP))
        {
            std::cout << "Jumped\n";
        }

        if (input.wasReleased(Action::QUIT))
        {
            CloseWindow();
        }
    }
}