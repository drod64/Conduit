#ifndef CONDUIT_GLFW_WINDOW_HPP
#define CONDUIT_GLFW_WINDOW_HPP
#include <cassert>
#include <glfw/glfw3.h>
#include <conduit/core/primitives.hpp>

namespace conduit::glfw {
class GLFWWindow {
private:
    GLFWwindow *m_glfw_window = nullptr;

public:
    GLFWWindow(uint32 width, uint32 height, const char *title);
    ~GLFWWindow();

    bool shouldClose() const;
    void close();

    void pollEvents();
    void swapBuffers();

    uint32 width() const;
    uint32 height() const;

    void setTitle(const char *title);

    bool isFocused() const;
    bool isMinimized() const;

    GLFWwindow* nativeHandle() const;
}; // class GLFWWindow
} // namespace conduit::glfw

#endif // CONDUIT_GLFW_WINDOW_HPP