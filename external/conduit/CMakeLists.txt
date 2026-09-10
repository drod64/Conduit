cmake_minimum_required(VERSION 3.20)

project(CONDUIT)

set(SOURCE_FILES
    src/framework/Time.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Link entt (version 4.0.0) to project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/entt/include)

# Link the project's own headers.
target_include_directories(${PROJECT_NAME} PUBLIC INCLUDE)