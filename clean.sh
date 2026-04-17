#!/bin/bash
# Clean build files script

echo "Cleaning build files..."

# Delete files in build directory
if [ -d "build" ]; then
    rm -rf build/*
    echo "Build directory cleaned"
fi

# Delete .app bundle
if [ -d "flock.app" ]; then
    rm -rf flock.app
    echo "flock.app deleted"
fi

echo "Cleanup complete!"
