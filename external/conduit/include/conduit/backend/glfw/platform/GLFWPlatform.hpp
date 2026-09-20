#ifndef CONDUIT_GLFW_PLATFORM_HPP
#define CONDUIT_GLFW_PLATFORM_HPP
#include <cassert>
#include <glfw/glfw3.h>
#include <conduit/backend/glfw/window/GLFWWindow.hpp>
#include <conduit/backend/glfw/input/GLFWInput.hpp>

namespace conduit::glfw {
    using Window = GLFWWindow;

    void initialize();

    void shutdown();
} // namespace conduit::glfw

#endif // CONDUIT_GLFW_PLATFORM_HPP