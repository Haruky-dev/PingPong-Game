cmake_minimum_required( VERSION 3.26 )

project(Bounce VERSION 1.0.0 LANGUAGES CXX)

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

find_package( SFML 3 REQUIRED COMPONENTS Graphics Window System Audio REQUIRED )

# src files (.cpp)
add_executable( ${PROJECT_NAME}
    src/main.cpp

    src/entities/Ball.cpp
    src/entities/Player.cpp
    src/entities/Utils.cpp

    src/cache/SoundCache.cpp
    src/cache/TextureCache.cpp
    src/cache/visuals/PlayUI.cpp
    src/cache/visuals/MenuUI.cpp
    src/cache/visuals/SettingUI.cpp

    src/engine/GameOver.cpp
    src/engine/Loading.cpp
    src/engine/MainMenu.cpp
    src/engine/Pause.cpp
    src/engine/Play.cpp
    src/engine/Quit.cpp
    src/engine/Setting.cpp
    src/engine/StateManager.cpp

    src/engine/input/InputManager.cpp

    src/json/Json.cpp
)

# link SFML libs
target_link_libraries( ${PROJECT_NAME} PRIVATE
    sfml-window
    sfml-system
    sfml-graphics
    sfml-audio
)

# include all .hpp files in /include
target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "game" )

# inc assets/ in build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets   

    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
        
    COMMENT "Copied [assets/] and [data/] directories..."
)