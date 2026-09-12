#include <conduit/tests/InputTester.hpp>

void conduit::InputTester::test()
{
    conduit::Input<Action> input;

    // Create bindings.
    conduit::Binding left;
    left.control = KEY_A;
    left.device = conduit::InputDevice::KEYBOARD;
    left.type = conduit::InputControlType::BUTTON;

    conduit::Binding right;
    right.control = KEY_D;
    right.device = conduit::InputDevice::KEYBOARD;
    right.type = conduit::InputControlType::BUTTON;

    conduit::Binding forward;
    forward.control = KEY_W;
    forward.device = conduit::InputDevice::KEYBOARD;
    forward.type = conduit::InputControlType::BUTTON;

    conduit::Binding backward;
    backward.control = KEY_S;
    backward.device = conduit::InputDevice::KEYBOARD;
    backward.type = conduit::InputControlType::BUTTON;

    conduit::Binding jump;
    jump.control = KEY_SPACE;
    jump.device = conduit::InputDevice::KEYBOARD;
    jump.type = conduit::InputControlType::BUTTON;

    conduit::Binding quit;
    quit.control = KEY_Q;
    quit.device = conduit::InputDevice::KEYBOARD;
    quit.type = conduit::InputControlType::BUTTON;

    // Bind actions to bindings.
    input.bind(Action::LEFT, left);
    input.bind(Action::RIGHT, right);
    input.bind(Action::QUIT, quit);
    input.bind(Action::FORWARD, forward);
    input.bind(Action::BACKWARD, backward);
    input.bind(Action::JUMP, jump);

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