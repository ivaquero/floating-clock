#!/bin/bash
# Cross-platform test script for Clouck

echo "Clouck Cross-Platform Test Suite"
echo "================================"
echo ""

# Detect operating system
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
    EXECUTABLE="./build/Clouck"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
    EXECUTABLE="./build/Clouck"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "win32" ]]; then
    OS="Windows"
    EXECUTABLE="./build/Clouck"
else
    echo "Unsupported operating system: $OSTYPE"
    exit 1
fi

echo "Detected OS: $OS"
echo "Executable: $EXECUTABLE"
echo ""

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "[ERROR] Executable not found: $EXECUTABLE"
    echo "Please build the project first using: ./build_cross_platform.sh"
    exit 1
fi

echo "[SUCCESS] Executable found"
echo ""

# Test 1: Basic functionality
echo "Test 1: Basic Clock Functionality"
echo "---------------------------------"
echo "• Starting Clouck application..."
echo "• Application should display a clock widget"
echo "• Clock should update every second"
echo ""

# Start the application in background
$EXECUTABLE &
PID=$!
sleep 3

# Check if application is running
if ps -p $PID >/dev/null; then
    echo "[SUCCESS] Application started successfully (PID: $PID)"
else
    echo "[ERROR] Application failed to start"
    exit 1
fi

echo ""
echo "Test 2: Always-on-Top Feature"
echo "------------------------------"
if [ "$OS" == "macOS" ]; then
    echo "• Open Safari or any other application"
    echo "• Enter fullscreen mode (Control + Command + F)"
    echo "• Clock should remain visible on top"
elif [ "$OS" == "Windows" ]; then
    echo "• Open any application in fullscreen mode"
    echo "• Clock should remain visible on top"
elif [ "$OS" == "Linux" ]; then
    echo "• Switch to different workspace"
    echo "• Clock should appear on all workspaces"
fi

echo ""
echo "Test 3: Resizable Feature"
echo "-------------------------"
echo "• Move mouse to bottom-right corner of clock"
echo "• Cursor should change to diagonal resize arrow"
echo "• Click and drag to resize"
echo "• Release mouse to save new size"

echo ""
echo "Test 4: Context Menu"
echo "---------------------"
echo "• Right-click on clock to show context menu"
echo "• Test various menu options:"
echo "  - Change color"
echo "  - Change font"
echo "  - Toggle always on top"
echo "  - Toggle click through"
echo "  - Quit application"

echo ""
echo "Platform-Specific Features:"
echo "---------------------------"
if [ "$OS" == "macOS" ]; then
    echo "• Native macOS window level integration"
    echo "• Support for all desktop spaces"
    echo "• Fullscreen mode compatibility"
elif [ "$OS" == "Windows" ]; then
    echo "• Windows native window management"
    echo "• Taskbar exclusion"
    echo "• Click-through support"
elif [ "$OS" == "Linux" ]; then
    echo "• X11 window manager integration"
    echo "• Workspace stickiness"
    echo "• EWMH (Extended Window Manager Hints) support"
fi

echo ""
echo "To stop testing:"
echo "• Right-click on clock and select 'Quit'"
echo "• Or run: kill $PID"
echo ""
echo "Test the features now! Press any key when finished..."
read -n 1 -s

echo ""
echo "Stopping application..."
kill $PID 2>/dev/null
sleep 1

echo ""
echo "Test completed!"
echo ""
echo "Configuration file location:"
echo "• macOS: ~/Library/Preferences/Clouck/config.xml"
echo "• Windows: %APPDATA%\\Clouck\\config.xml"
echo "• Linux: ~/.config/Clouck/config.xml"
