#include <conduit/tests/InputTester.hpp>

void conduit::InputTester::test()
{
    conduit::Input<Action> input;

    // Create bindings.
    conduit::Binding jump;
    jump.control = MOUSE_BUTTON_RIGHT;
    jump.device = conduit::InputDevice::MOUSE;
    jump.type = conduit::InputControlType::BUTTON;

    conduit::Binding quit;
    quit.control = KEY_Q;
    quit.device = conduit::InputDevice::KEYBOARD;
    quit.type = conduit::InputControlType::BUTTON;

    // Bind actions to bindings.
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

        if (input.wasPressed(Action::JUMP))
        {
            std::cout << "Just pressed\n";
        }

        if (input.isDown(Action::JUMP))
        {
            std::cout << "Held down\n";
        }
        
        if (input.wasReleased(Action::JUMP))
        {
            std::cout << "Just released\n";
        }

        if (input.wasPressed(Action::QUIT))
        {
            CloseWindow();
        }
    }
}