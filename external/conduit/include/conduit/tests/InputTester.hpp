#ifndef CONDUIT_INPUT_TESTER_HPP
#define CONDUIT_INPUT_TESTER_HPP
#include <iostream>
#include <conduit/core/primitives.hpp>
#include <conduit/framework/input/Input.hpp>
#include <conduit/framework/input/ActionMap.hpp>
#include <conduit/framework/input/glfw/GLFWInput.hpp>

namespace conduit {
class InputTester {
public:
    enum class Action : conduit::uint16 {
        FORWARD, BACKWARD, LEFT, RIGHT, JUMP, QUIT
    };

    InputTester() = default;
    ~InputTester() = default;

    void test();
}; // class InputTester
} // namespace conduit

#endif // INPUT_TESTER_HPP