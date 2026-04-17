#!/bin/bash
# Cross-platform build script for Clouck

echo "Building Clouck - Cross-platform Clock Application"
echo "=================================================="

# Detect operating system
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "win32" ]]; then
    OS="Windows"
else
    echo "Unsupported operating system: $OSTYPE"
    exit 1
fi

echo "Detected OS: $OS"
echo ""

# Create build directory
mkdir -p build

# Clean old build files
echo "Cleaning old build files..."
rm -rf build/*

# Build using CMake (cross-platform)
echo "Configuring with CMake..."
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

echo "Building project..."
cmake --build build --config Release

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "Build successful!"
echo ""
echo "Executable location:"

if [ "$OS" == "macOS" ]; then
    echo "  - build/Clouck.app/Contents/MacOS/Clouck (macOS)"
elif [ "$OS" == "Windows" ]; then
    echo "  - build/Release/Clouck.exe (Windows)"
elif [ "$OS" == "Linux" ]; then
    echo "  - build/Clouck (Linux)"
fi

echo ""
echo "To run the application:"
if [ "$OS" == "macOS" ]; then
    echo "  ./build/Clouck.app/Contents/MacOS/Clouck"
elif [ "$OS" == "Windows" ]; then
    echo "  ./build/Release/Clouck.exe"
elif [ "$OS" == "Linux" ]; then
    echo "  ./build/Clouck"
fi
