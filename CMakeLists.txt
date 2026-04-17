cmake_minimum_required(VERSION 3.16)
project(flock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Set up Qt6
qt6_standard_project_setup()

# Sources
set(SOURCES
    main.cpp
    clockwidget.cpp
    configmanager.cpp
)

set(HEADERS
    clockwidget.h
    configmanager.h
)

# Create executable
qt6_add_executable(flock
    ${SOURCES}
    ${HEADERS}
)

# Link Qt libraries
target_link_libraries(flock
    Qt6::Core
    Qt6::Widgets
)

# Set up install
install(TARGETS flock
    RUNTIME DESTINATION bin
)
