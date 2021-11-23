cmake_minimum_required(VERSION 3.5)

project(OpenGL-particles VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets OpenGL REQUIRED)

set(PROJECT_HEADERS
    mainwindow.h
    scene.h
    renderwidget.h
    camera.h
    particlesystem.h
    geometryobject.h
    renderableobject.h
    light.h
    directionallight.h
    gldebug.h
    testbox.h)

set(PROJECT_SOURCES
        main.cpp
        shaders.qrc
        mainwindow.cpp
        scene.cpp
        renderwidget.cpp
        camera.cpp
        particlesystem.cpp
        geometryobject.cpp
        renderableobject.cpp
        light.cpp
        directionallight.cpp
        gldebug.cpp
        testbox.cpp)

set(PROJECT_FORMS
    mainwindow.ui)

add_executable(OpenGL-particles ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_FORMS})

target_link_libraries(OpenGL-particles PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL ${OPENGL_LIBRARIES})
