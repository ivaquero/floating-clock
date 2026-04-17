# Build and Run Test

echo "Building QFlock with XML configuration..."

# Clean previous build
./clean.sh

# Build the project
./build.sh

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Testing XML configuration..."

    # Show config file content
    echo "Config file content:"
    if [ -f "config.xml" ]; then
        cat config.xml
    else
        echo "No config.xml found (will be created on first run)"
    fi

    echo ""
    echo "You can now run the application:"
    echo "./build/flock.app/Contents/MacOS/flock  # macOS"
    echo "./build/flock                           # Linux"
else
    echo "Build failed!"
fi
