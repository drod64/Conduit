#include <conduit/tests/InputTester.hpp>

void conduit::InputTester::test()
{
    conduit::platform::initialize();

    m_window = conduit::Window(100, 100, "Conduit Input Tester.");
    
    conduit::Input input(m_window);

    conduit::ActionMap<Action> actions(input, 0);

    // -1 for forwards
    actions.bind(Action::FORWARD,   InputControl::key(Key::W), -1);
    actions.bind(Action::FORWARD,   InputControl::key(Key::UP), -1);
    actions.bind(Action::FORWARD,   InputControl::gamepadButton(GamepadButton::D_PAD_UP), -1);
    actions.bind(Action::FORWARD,   InputControl::gamepadAxis(GamepadAxis::LEFT_STICK_Y));

    // -1 for left
    actions.bind(Action::LEFT,      InputControl::key(Key::A), -1);
    actions.bind(Action::LEFT,      InputControl::key(Key::LEFT), -1);
    actions.bind(Action::LEFT,      InputControl::gamepadButton(GamepadButton::D_PAD_LEFT), -1);
    actions.bind(Action::LEFT,      InputControl::gamepadAxis(GamepadAxis::LEFT_STICK_X));

    // +1 for backwards
    actions.bind(Action::BACKWARD,  InputControl::key(Key::S));
    actions.bind(Action::BACKWARD,  InputControl::key(Key::DOWN));
    actions.bind(Action::BACKWARD,  InputControl::gamepadButton(GamepadButton::D_PAD_DOWN));
    actions.bind(Action::BACKWARD,  InputControl::gamepadAxis(GamepadAxis::LEFT_STICK_Y));

    // +1 for right
    actions.bind(Action::RIGHT,     InputControl::key(Key::D));
    actions.bind(Action::RIGHT,     InputControl::key(Key::RIGHT));
    actions.bind(Action::RIGHT,     InputControl::gamepadButton(GamepadButton::D_PAD_RIGHT));
    actions.bind(Action::RIGHT,     InputControl::gamepadAxis(GamepadAxis::LEFT_STICK_X));

    // No direction scale needed from here
    actions.bind(Action::JUMP,      InputControl::key(Key::SPACE));
    actions.bind(Action::JUMP,      InputControl::gamepadButton(GamepadButton::A));

    actions.bind(Action::QUIT,      InputControl::key(Key::Q));
    actions.bind(Action::QUIT,      InputControl::gamepadButton(GamepadButton::START));

    conduit::real deadzone = 0.5;

    // Simple loop to poll input
    while (!m_window.shouldClose())
    {
        // Poll events.
        m_window.pollEvents();

        // Poll input.
        input.poll();
        
        // Poll actions.
        actions.poll();

        if (input.mouse().wheel().y > 0)
        {
            std::cout << "Mouse scrolling up\n";
        }

        if (input.mouse().wheel().y < 0)
        {
            std::cout << "Mouse scrolling down\n";
        }

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
            m_window.close();
        }
    }

    conduit::platform::shutdown();
}