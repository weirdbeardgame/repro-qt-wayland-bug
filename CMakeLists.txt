cmake_minimum_required(VERSION 3.12)

project(attach-bug)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
	main.cpp
	MainWindow.h
	MainWindow.cpp
	MainWindow.ui
)

qt_add_executable(attach_bug ${PROJECT_SOURCES})

target_link_libraries(attach_bug PRIVATE Qt6::Widgets)
