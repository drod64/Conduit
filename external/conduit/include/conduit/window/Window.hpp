#ifndef CONDUIT_WINDOW_HPP
#define CONDUIT_WINDOW_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/backend/Platform.hpp>

namespace conduit {
class Input;

class Window {
private:
    friend class Input;
    platform::Window m_platform_window;

public:
    Window(uint32 width, uint32 height, const char *title);
    ~Window() = default;

    bool shouldClose() const;
    void close();

    void pollEvents();
    void swapBuffers();

    uint32 width() const;
    uint32 height() const;

    void setTitle(const char *title);

    bool isFocused() const;
    bool isMinimized() const;
}; // class Window
} // namespace conduit

#endif // CONDUIT_WINDOW_HPP