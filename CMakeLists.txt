cmake_minimum_required(VERSION 3.26)
project(Test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Setze den Pfad zu SDL2
set(SDL2_DIR "C:/Users/fabia/OneDrive/Dokumente/C/GameEngine/Fabinite_Engine/SDL2-2.30.9")

# SDL2 Header und Bibliotheken einbinden
include_directories(${SDL2_DIR}/include)
link_directories(${SDL2_DIR}/lib/x64)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# Definiere das ausführbare Ziel
add_executable(Test WIN32 main.cpp
        SDLWidget.cpp
        SDLWidget.h
        MainWindow.cpp
        MainWindow.h
        utils.cpp
        utils.h)

# Verlinke die Bibliotheken
target_link_libraries(Test
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ${SDL2_DIR}/lib/x64/SDL2.lib
)


# Zusätzliche Konfigurationen für Windows
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
