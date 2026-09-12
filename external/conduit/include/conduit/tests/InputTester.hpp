#ifndef CONDUIT_INPUT_TESTER_HPP
#define CONDUIT_INPUT_TESTER_HPP
#include <iostream>
#include <conduit/core/primitives.hpp>
#include <conduit/framework/Input.hpp>

namespace conduit {
class InputTester {
public:
    enum class Action : conduit::uint16 {
        FORWARD, BACKWARD, LEFT, RIGHT, JUMP, QUIT
    };

    void test();
}; // class InputTester
} // namespace conduit

#endif // INPUT_TESTER_HPP