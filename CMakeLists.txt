cmake_minimum_required(VERSION 3.20)

project(TEST_GAME)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -static")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Our Project
set(
    SOURCE_FILES
    src/main.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif ()

# Link conduit library.
add_subdirectory(${CMAKE_SOURCE_DIR}/external/conduit)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/conduit/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/conduit)
target_link_libraries(${PROJECT_NAME} CONDUIT)

# Link SM library
add_subdirectory(${CMAKE_SOURCE_DIR}/external/sm)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/sm/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/sm)
target_link_libraries(${PROJECT_NAME} SM)