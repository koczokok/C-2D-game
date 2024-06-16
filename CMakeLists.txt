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
        Room/tile.h
        Room/tile.cpp
        Game/world.h
        Game/world.cpp
        Characters/player/Character.h
        Characters/player/Character.cpp
        Characters/projectile.h
        Characters/projectile.cpp
        Characters/Enemy.cpp
        Characters/Enemy.h
        Characters/Casual.cpp
        Characters/Casual.h
        Characters/Speedy.cpp
        Characters/Speedy.h
        Characters/Fatman.cpp
        Characters/Fatman.h
        Characters/Boss.cpp
        Characters/Boss.h
        Room/Room.cpp
        Room/Room.h
        Menus/Menu.cpp
        Menus/Menu.h
        Game/GameStates.h
        Game/game.cpp
        Game/game.h
        Characters/eType.h
        Game/HUD.cpp
        Game/HUD.h
        Menus/mainMenu.cpp
        Menus/mainMenu.h
        Game/gameWon.cpp
        Game/gameWon.h

)

target_link_libraries(PJC_Game sfml-graphics)
target_link_libraries(PJC_Game fmt)
