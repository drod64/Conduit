#include <conduit/tests/InputTester.hpp>

void conduit::InputTester::test()
{
    conduit::ActionMap<Action> actions(m_input, 0);

    // -1 for forwards
    actions.bind(Action::FORWARD,   Key::W, -1);
    actions.bind(Action::FORWARD,   Key::UP, -1);
    actions.bind(Action::FORWARD,   GamepadButton::D_PAD_UP, -1);
    actions.bind(Action::FORWARD,   GamepadAxis::LEFT_STICK_Y);

    // -1 for left
    actions.bind(Action::LEFT,      Key::A, -1);
    actions.bind(Action::LEFT,      Key::LEFT, -1);
    actions.bind(Action::LEFT,      GamepadButton::D_PAD_LEFT, -1);
    actions.bind(Action::LEFT,      GamepadAxis::LEFT_STICK_X);

    // +1 for backwards
    actions.bind(Action::BACKWARD,  Key::S);
    actions.bind(Action::BACKWARD,  Key::DOWN);
    actions.bind(Action::BACKWARD,  GamepadButton::D_PAD_DOWN);
    actions.bind(Action::BACKWARD,  GamepadAxis::LEFT_STICK_Y);

    // +1 for right
    actions.bind(Action::RIGHT,     Key::D);
    actions.bind(Action::RIGHT,     Key::RIGHT);
    actions.bind(Action::RIGHT,     GamepadButton::D_PAD_RIGHT);
    actions.bind(Action::RIGHT,     GamepadAxis::LEFT_STICK_X);

    // No direct scale needed from here
    actions.bind(Action::JUMP,      Key::SPACE);
    actions.bind(Action::JUMP,      MouseButton::RIGHT);
    actions.bind(Action::JUMP,      GamepadButton::A);

    actions.bind(Action::QUIT,      Key::Q);
    actions.bind(Action::QUIT,      GamepadButton::START);

    conduit::real deadzone = 0.5;

    // Initialize window
    InitWindow(100, 100, "conduit::InputTester.cpp");
    SetTargetFPS(conduit::config::TARGET_FRAME_RATE);

    // Simple loop to poll input
    while (!WindowShouldClose())
    {
        PollInputEvents();

        // Poll hardware.
        m_raylib_input.poll(m_input);
        
        // Poll actions.
        actions.poll();

        if (actions.value(Action::FORWARD) < -deadzone)
        {
            std::cout << "Moving forward\n";
        }
        
        if (actions.value(Action::BACKWARD) > deadzone)
        {
            std::cout << "Moving backward\n";
        }

        if (actions.value(Action::LEFT) < -deadzone)
        {
            std::cout << "Moving left\n";
        }
        
        if (actions.value(Action::RIGHT) > deadzone)
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