#ifndef CONDUIT_MOUSE_STATE_HPP
#define CONDUIT_MOUSE_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/bitset.hpp>
#include <conduit/framework/input/mouse/MouseButton.hpp>
#include <sm/Vec2.h>

namespace conduit {
class MouseState {
private:
    bitset<static_cast<sizet>(MouseButton::MAX_COUNT)> m_current{};
    bitset<static_cast<sizet>(MouseButton::MAX_COUNT)> m_previous{};

    sm::Vec2 m_position{};
    sm::Vec2 m_delta{};
    sm::Vec2 m_wheel{};

public:
    MouseState() = default;
    ~MouseState() = default;

    bool isDown(MouseButton mouse_button) const;
    bool wasPressed(MouseButton mouse_button) const;
    bool wasReleased(MouseButton mouse_button) const;
    sm::Vec2 position() const;
    sm::Vec2 delta() const;
    sm::Vec2 wheel() const;

    void reset();
    void setButton(MouseButton mouse_button, bool state);
    void setPosition(sm::Vec2 position);
    void setDelta(sm::Vec2 delta);
    void setWheel(sm::Vec2 wheel);
    void updatePrevious();

}; // class MouseState
} // namespace conduit

#endif // CONDUIT_MOUSE_STATE_HPP