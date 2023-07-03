cmake_minimum_required(VERSION 3.14)

project(TestPythonAndC LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(TestPythonAndC
  main.cpp
)
target_link_libraries(TestPythonAndC Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS TestPythonAndC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

INCLUDE_DIRECTORIES(F:\\Tools\\Ana\\pkgs\\python-3.8.16-h6244533_3\\include)

LINK_DIRECTORIES(F:\\Tools\\Ana\\pkgs\\python-3.8.16-h6244533_3\\libs)
