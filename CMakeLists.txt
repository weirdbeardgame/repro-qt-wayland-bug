cmake_minimum_required(VERSION 3.12)

project(attach-bug)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC)

set(CMAKE_CXX_STANDARD 20)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS WaylandCompositor)

add_subdirectory(extern/fmt)
add_subdirectory(extern/glad)

set(PROJECT_SOURCES
	main.cpp
	MainWindow.h
	MainWindow.cpp
	MainWindow.ui
	ReplacementWidget.cpp
	ReplacementWidget.h
	InitialWidget.cpp
	InitialWidget.h
	InitialWidget.ui
    DisplayWidget.h
    DisplayWidget.cpp
    GLContextEGL.h
    GLContextEGL.cpp
)

qt_add_executable(attach_bug ${PROJECT_SOURCES})

target_link_libraries(attach_bug PRIVATE Qt6::Widgets)
target_link_libraries(attach_bug PRIVATE Qt6::WaylandCompositor)
target_link_libraries(attach_bug PRIVATE glad)
target_link_libraries(attach_bug PRIVATE fmt)