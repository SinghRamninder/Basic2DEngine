cmake_minimum_required(VERSION 3.20)

project(Basic2DEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.16
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SDL)

add_executable(Basic2DEngine
    src/main.cpp
    src/Player.cpp
)

target_link_libraries(Basic2DEngine
    PRIVATE
    SDL3::SDL3
)

if(WIN32)
    add_custom_command(
        TARGET Basic2DEngine POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "$<TARGET_FILE:SDL3::SDL3-shared>"
                "$<TARGET_FILE_DIR:Basic2DEngine>"
        VERBATIM
    )
endif()