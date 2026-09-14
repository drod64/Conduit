#ifndef CONDUIT_RAYLIB_INPUT_HPP
#define CONDUIT_RAYLIB_INPUT_HPP
#include <conduit/framework/input/Input.hpp>
#include <conduit/framework/input/raylib/RaylibButtonMapping.hpp>

namespace conduit::raylib {
class RaylibInput {
private:
    void pollKeyboard(Input &input);

    void pollMouse(Input &input);

    void pollGamepads(Input &input);

public:
    RaylibInput() = default;
    ~RaylibInput() = default;

    void poll(Input &input);
}; // class RaylibInput
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_INPUT_HPP