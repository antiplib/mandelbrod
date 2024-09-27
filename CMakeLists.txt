cmake_minimum_required(VERSION 3.29)
project(mondelbrod)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(mondelbrod main.cpp
        complex.cpp
        complex.h
        Label.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        begin.cpp
        begin.h
        begin.ui
        jullian.cpp
        jullian.h
)
target_link_libraries(mondelbrod
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

