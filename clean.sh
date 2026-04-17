#!/bin/bash
# Clean build files script

echo "Cleaning build files..."

# Delete files in build directory
if [ -d "build" ]; then
    rm -rf build/*
    echo "Build directory cleaned"
fi

# Delete .app bundle
if [ -d "Clouck.app" ]; then
    rm -rf Clouck.app
    echo "Clouck.app deleted"
fi

echo "Cleanup complete!"
