cmake_minimum_required(VERSION 3.16)
project(Clouck)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Platform-specific dependencies
if(WIN32)
    # Windows-specific libraries
    set(PLATFORM_LIBS user32 dwmapi gdi32 kernel32)
elseif(UNIX AND NOT APPLE)
    # Linux-specific libraries
    find_package(X11 REQUIRED)
    set(PLATFORM_LIBS ${X11_LIBRARIES} Xfixes)
endif()

# Set up Qt6
qt6_standard_project_setup()

# Sources
set(SOURCES
    main.cpp
    clock_widget.cpp
    config_manager.cpp
    window_helper.cpp
)

set(HEADERS
    clock_widget.h
    config_manager.h
    window_helper.h
)

# Platform-specific headers
if(WIN32)
    list(APPEND HEADERS window_helper_windows.h)
elseif(UNIX AND NOT APPLE)
    list(APPEND HEADERS window_helper_linux.h)
elseif(APPLE)
    list(APPEND HEADERS window_helper_macos.h)
endif()

# Create executable
qt6_add_executable(Clouck WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
)

# Platform-specific sources and libraries
if(APPLE)
    target_sources(Clouck PRIVATE window_helper_macos.mm)
    target_link_libraries(Clouck PRIVATE "-framework AppKit" "-framework CoreGraphics")
endif()

if(WIN32)
    target_sources(Clouck PRIVATE window_helper_windows.cpp)
    target_link_libraries(Clouck PRIVATE user32 dwmapi)
endif()

if(UNIX AND NOT APPLE)
    target_sources(Clouck PRIVATE window_helper_linux.cpp)
    target_link_libraries(Clouck PRIVATE ${X11_LIBRARIES} Xfixes)
endif()

# Link Qt libraries
target_link_libraries(Clouck PRIVATE Qt6::Core Qt6::Widgets)

# Set up install
install(TARGETS Clouck
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION bin
)
