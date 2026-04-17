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
qmake flock.pro

# Build project
echo "Starting compilation..."
make

# Check build result
if [ -f "build/flock.app/Contents/MacOS/flock" ] || [ -f "build/flock" ]; then
    echo "Build successful!"
    echo "Executable location:"
    [ -f "build/flock.app/Contents/MacOS/flock" ] && echo "  - build/flock.app/Contents/MacOS/flock (macOS)"
    [ -f "build/flock" ] && echo "  - build/flock (Linux)"
else
    echo "Build failed!"
    exit 1
fi
