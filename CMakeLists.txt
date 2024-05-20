cmake_minimum_required(VERSION 3.27)
project(PJC_Game)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)

FetchContent_MakeAvailable(fmt)

add_executable(PJC_Game main.cpp
        tile.h
        tile.cpp
        world.h
        world.cpp
        character.h
        character.cpp
        projectile.h
        projectile.cpp
)

target_link_libraries(PJC_Game sfml-graphics)
target_link_libraries(PJC_Game fmt)
