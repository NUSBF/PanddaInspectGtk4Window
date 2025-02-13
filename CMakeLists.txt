cmake_minimum_required(VERSION 3.14)

project(PanddaInspectGtk4Window LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# Find GTK4
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

add_executable(PanddaInspectGtk4Window
  main.cpp
)

target_link_libraries(PanddaInspectGtk4Window
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    PkgConfig::GTK4
)

# Copy the XML file to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Pandda2InspectGTK4Window.xml
               ${CMAKE_CURRENT_BINARY_DIR}/Pandda2InspectGTK4Window.xml COPYONLY)
