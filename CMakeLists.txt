cmake_minimum_required(VERSION 3.11)
project(ChessEngineOOP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Find or download Raylib
find_package(raylib QUIET)

if(NOT raylib_FOUND)
    message(STATUS "raylib not found locally. Fetching raylib via FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/4.5.0.tar.gz
    )
    # Exclude raylib examples and games from building
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

# Gather all source files from the src directory automatically
file(GLOB SOURCES "src/*.cpp")

# 1. Create the executable target with the correct standardized name
add_executable(ChessEngineOOP ${SOURCES})

# 2. Link Raylib to your target
target_link_libraries(ChessEngineOOP PRIVATE raylib)

# Extra system libraries for linking raylib on Linux/macOS if we did find_package
if(UNIX AND raylib_FOUND)
    if(APPLE)
        target_link_libraries(ChessEngineOOP PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL" "-framework CoreVideo")
    else()
        target_link_libraries(ChessEngineOOP PRIVATE GL rt dl m X11 pthread)
    endif()
endif()

# 3. Copy the assets directory straight to the build output folder POST-BUILD
add_custom_command(TARGET ChessEngineOOP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/3d_wood"
    "$<TARGET_FILE_DIR:ChessEngineOOP>/3d_wood"
)