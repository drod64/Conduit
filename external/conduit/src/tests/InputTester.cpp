#include <conduit/tests/InputTester.hpp>

void conduit::InputTester::test()
{
    conduit::ActionMap<Action> actions(m_input);

    // Bind actions to bindings.
    actions.bind(Action::FORWARD,   Key::W);
    actions.bind(Action::FORWARD,   Key::UP);
    actions.bind(Action::LEFT,      Key::A);
    actions.bind(Action::LEFT,      Key::LEFT);
    actions.bind(Action::BACKWARD,  Key::S);
    actions.bind(Action::BACKWARD,  Key::DOWN);
    actions.bind(Action::RIGHT,     Key::D);
    actions.bind(Action::RIGHT,     Key::RIGHT);
    actions.bind(Action::JUMP,      Key::SPACE);
    actions.bind(Action::JUMP,      MouseButton::RIGHT);
    actions.bind(Action::QUIT,      Key::Q);

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