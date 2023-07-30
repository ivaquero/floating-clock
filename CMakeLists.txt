cmake_minimum_required(VERSION 3.5)
project(clock)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(
    .
)

set (SRCS
    clock.cpp
    clock.h
    main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)
