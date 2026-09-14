cmake_minimum_required(VERSION 3.20)

project(CONDUIT)

set(SOURCE_FILES
    src/framework/input/gamepad/GamepadInput.cpp

    src/framework/input/raylib/RaylibInput.cpp
    src/framework/input/raylib/RaylibInputMapping.cpp

    src/framework/input/Input.cpp
    
    src/framework/Time.cpp
    
    src/tests/InputTester.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Link raylib library.
target_link_libraries(${PROJECT_NAME} raylib)

# Link custom math library.
target_link_libraries(${PROJECT_NAME} SM)

# Link entt (version 4.0.0) to project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/entt/include)

# Link the project's own headers.
target_include_directories(${PROJECT_NAME} PUBLIC INCLUDE)