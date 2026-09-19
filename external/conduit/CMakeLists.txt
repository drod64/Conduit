cmake_minimum_required(VERSION 3.20)

project(CONDUIT)

# Dependencies
set(GLFW_VERSION 3.5.1)
find_package(glfw3 ${GLFW_VERSION} QUIET) # QUIET or REQUIRED
if (NOT glfw3_FOUND) # If there's none, fetch and build glfw
    include(FetchContent)
    FetchContent_Declare(
        glfw
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz
    )
    FetchContent_GetProperties(glfw)
    if (NOT glfw_POPULATED) # Have we downloaded glfw yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(glfw)
    endif()
endif()

set(
    SOURCE_FILES
    src/framework/input/gamepad/GamepadState.cpp
    src/framework/input/keyboard/KeyboardState.cpp
    src/framework/input/mouse/MouseState.cpp

    src/framework/input/Input.cpp
    
    src/framework/Time.cpp
    
    # src/tests/InputTester.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Link glfw to conduit
target_link_libraries(${PROJECT_NAME} glfw)

# Link custom math directory to conduit
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/sm/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/sm)
target_link_libraries(${PROJECT_NAME} SM)

# Link entt (version 4.0.0) to conduit
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/entt/include)

# Link the project's own headers.
target_include_directories(${PROJECT_NAME} PUBLIC INCLUDE)