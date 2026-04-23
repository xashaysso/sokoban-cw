cmake_minimum_required(VERSION 3.28)
project(cw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)

set(SFML_BUILD_AUDIO ON)
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_EXAMPLES OFF)

FetchContent_MakeAvailable(SFML)

add_executable(cw WIN32 main.cpp
        resource.rc
        entities/Player.cpp
        entities/Box.cpp
        core/Map.cpp
        core/Level.cpp
        graphics/LevelRenderer.cpp
        core/StateManager.cpp
        states/PlayState.cpp
        states/MenuState.cpp
        graphics/MenuRenderer.cpp
        states/PauseState.cpp
        graphics/PauseRenderer.cpp
        core/AudioManager.cpp
        states/WinState.cpp
        graphics/WinRenderer.cpp
        states/ControlsState.cpp
)

target_link_libraries(cw PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

if(WIN32)
    add_custom_command(TARGET cw POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:cw>
    )
    add_custom_command(TARGET cw POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:cw>/assets"
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            "${CMAKE_SOURCE_DIR}/levels"
            "$<TARGET_FILE_DIR:cw>/levels"
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            "${CMAKE_SOURCE_DIR}/fonts"
            "$<TARGET_FILE_DIR:cw>/fonts"
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            "${CMAKE_SOURCE_DIR}/audio"
            "$<TARGET_FILE_DIR:cw>/audio"
    )
endif()
