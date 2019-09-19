cmake_minimum_required(VERSION 3.1.0)

project(Qt_TP2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Qt_TP2
        MainWindow.cpp
        main.cpp
        Canvas.cpp
        Canvas.h
        Shape.h
        Rectangle.h
        Line.h
        Line.cpp
        Rectangle.cpp
        Ellipse.cpp
        Ellipse.h)

target_link_libraries(Qt_TP2 Qt5::Widgets)