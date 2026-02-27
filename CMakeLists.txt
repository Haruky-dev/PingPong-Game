cmake_minimum_required( VERSION 3.26 )

project(bounce VERSION 1.0.0 LANGUAGES CXX)

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

find_package( SFML 3 REQUIRED COMPONENTS Graphics Window System Audio REQUIRED )

# src files (.cpp)
add_executable( ${PROJECT_NAME}
    src/main.cpp

    src/entities/Ball.cpp
    src/entities/Player.cpp

    src/tools/Tool.cpp
    src/tools/Math.cpp
    src/tools/Json.cpp
    src/tools/FrameRate.cpp

    src/cache/SoundCache.cpp
    src/cache/TextureCache.cpp
    src/cache/visuals/MenuUI.cpp
    src/cache/visuals/PlayUI.cpp
    src/cache/visuals/SettingUI.cpp
    
    src/engine/StateManager.cpp
    src/engine/states/Play.cpp
    src/engine/states/Quit.cpp
    src/engine/states/Pause.cpp
    src/engine/states/Loading.cpp
    src/engine/states/Setting.cpp    
    src/engine/states/MainMenu.cpp
    src/engine/states/GameOver.cpp
    src/engine/input/InputManager.cpp
)

# link SFML libs
target_link_libraries( ${PROJECT_NAME} PRIVATE
    sfml-audio
    sfml-window
    sfml-system
    sfml-graphics
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "game" )
set_source_files_properties( ${CMAKE_SOURCE_DIR}/src/tools/Json.cpp
    PROPERTIES OBJECT_DEPENDS ${CMAKE_SOURCE_DIR}/data/conf.json )

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