#include <conduit/framework/input/mouse/MouseState.hpp>

bool conduit::MouseState::isDown(MouseButton mouse_button) const
{
    sizet index = static_cast<sizet>(mouse_button);

    return m_current.test(index);
}

bool conduit::MouseState::wasPressed(MouseButton mouse_button) const
{
    sizet index = static_cast<sizet>(mouse_button);

    return !m_previous.test(index) && m_current.test(index);
}

bool conduit::MouseState::wasReleased(MouseButton mouse_button) const
{
    sizet index = static_cast<sizet>(mouse_button);

    return m_previous.test(index) && !m_current.test(index);
}

sm::Vec2 conduit::MouseState::position() const
{
    return m_position;
}

sm::Vec2 conduit::MouseState::delta() const
{
    return m_delta;
}

sm::Vec2 conduit::MouseState::wheel() const
{
    return m_wheel;
}

void conduit::MouseState::reset()
{
    m_current.reset();
    m_previous.reset();
    m_position = {static_cast<real>(0), static_cast<real>(0)};
    m_delta = {static_cast<real>(0), static_cast<real>(0)};
    m_wheel = {static_cast<real>(0), static_cast<real>(0)};
}

void conduit::MouseState::setButton(MouseButton mouse_button, bool state)
{
    sizet index = static_cast<sizet>(mouse_button);

    m_current.set(index, state);
}

void conduit::MouseState::setPosition(sm::Vec2 position)
{
    m_position = position;
}

void conduit::MouseState::setDelta(sm::Vec2 delta)
{
    m_delta = delta;
}

void conduit::MouseState::setWheel(sm::Vec2 wheel)
{
    m_wheel = wheel;
}

void conduit::MouseState::updatePrevious()
{
    m_previous = m_current;
}