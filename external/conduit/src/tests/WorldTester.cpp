#include <conduit/tests/WorldTester.hpp>
#include <iostream>

void conduit::WorldTester::test()
{
    testRegistry();
}

void conduit::WorldTester::testRegistry()
{
    conduit::platform::initialize();

    m_window = Window(100, 100, "WorldTester");
    Input input(m_window);
    ActionMap<std::string> actionMap(input);

    actionMap.bind("spawn entity",      Binding(InputControl::mouseButton(MouseButton::LEFT)));
    actionMap.bind("loop entities",     Binding(InputControl::key(Key::LEFT_SHIFT)));
    actionMap.bind("clear world",       Binding(InputControl::key(Key::BACKSPACE)));
    actionMap.bind("quit",              Binding(InputControl::key(Key::ESCAPE)));

    while (!m_window.shouldClose())
    {
        m_window.pollEvents();
        input.poll();
        actionMap.poll();

        if (actionMap.wasPressed("spawn entity"))
        {
            spawnTestEntity();
        }

        if (actionMap.wasPressed("loop entities"))
        {
            m_world.view<Position2D, Velocity2D>().each([] (entt::entity e, Position2D &pos, Velocity2D &vel) {
                std::cout << "Entity: " << entt::to_integral(e) << '\n';
                std::cout << "Position: " << "(" << pos.x << ", " << pos.y << ")\n";
                std::cout << "Velocity: " << "(" << vel.y << ", " << vel.y << ")\n"; 
            });
        }

        if (actionMap.wasPressed("clear world"))
        {
            m_world.clear();
        }

        if (actionMap.wasPressed("quit"))
        {
            m_window.close();
        }
    }

    conduit::platform::shutdown();
}

void conduit::WorldTester::spawnTestEntity()
{
    Position2D pos;

    Velocity2D vel;

    entt::entity e = m_world.createEntity();

    m_world.emplaceComponent<Position2D>(e, pos);
    m_world.emplaceComponent<Velocity2D>(e, vel);
}