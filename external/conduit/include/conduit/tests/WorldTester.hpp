#ifndef CONDUIT_WORLD_TESTER_HPP
#define CONDUIT_WORLD_TESTER_HPP
#include <conduit/framework/World.hpp>
#include <conduit/window/Window.hpp>
#include <conduit/input/Input.hpp>
#include <conduit/input/ActionMap.hpp>

namespace conduit {
class WorldTester {
public:
    void test();

private:
    Window  m_window;
    World   m_world;

    struct Position2D {
        real x{};
        real y{};
    };

    struct SpecialTag{};

    struct Velocity2D {
        real x{};
        real y{};
    };

    void testRegistry();

    void spawnTestEntity();
}; // class WorldTester
} // namespace conduit

#endif // CONDUIT_WORLD_TESTER_HPP