cmake_minimum_required(VERSION 3.7...3.21)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(FloatingClock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "v")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Homebrew Qt6 路径 (自动检测或手动设置)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # 检测架构
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        set(QT6_PATH "/opt/homebrew/opt/qt" CACHE PATH "Qt6 installation path")
    else()
        set(QT6_PATH "/usr/local/opt/qt" CACHE PATH "Qt6 installation path")
    endif()

    # 添加到 CMake 搜索路径
    list(APPEND CMAKE_PREFIX_PATH "${QT6_PATH}/lib/cmake")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Xml)

add_executable(${CMAKE_PROJECT_NAME} WIN32 MACOSX_BUNDLE main.cpp)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Xml
)

# macOS 特定设置
if(APPLE)
    set_target_properties(FloatingClock PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist.in
    )

    # 修复运行时库路径
    set_target_properties(FloatingClock PROPERTIES
        INSTALL_RPATH "${QT6_PATH}/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()
