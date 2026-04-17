#!/bin/bash
# Build script

echo "Starting QFlock build..."

# Create build directory if it doesn't exist
mkdir -p build

# Clean old build files
echo "Cleaning old build files..."
rm -rf build/*

# Generate Makefile using qmake
echo "Generating Makefile..."
qmake Clouck.pro

# Build project
echo "Starting compilation..."
make

# Check build result
if [ -f "build/Clouck.app/Contents/MacOS/Clouck" ] || [ -f "build/Clouck" ]; then
    echo "Build successful!"
    echo "Executable location:"
    [ -f "build/Clouck.app/Contents/MacOS/Clouck" ] && echo "  - build/Clouck.app/Contents/MacOS/Clouck (macOS)"
    [ -f "build/Clouck" ] && echo "  - build/Clouck (Linux)"
else
    echo "Build failed!"
    exit 1
fi
