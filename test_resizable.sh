#!/bin/bash

echo "Testing QFlock Resizable Feature"
echo "================================"
echo ""
echo "1. Starting QFlock application..."
./build/Clouck.app/Contents/MacOS/Clouck &
PID=$!

sleep 2

echo ""
echo "2. Checking if application is running..."
if ps -p $PID >/dev/null; then
    echo "[SUCCESS] Application started successfully (PID: $PID)"
else
    echo "[ERROR] Application failed to start"
    exit 1
fi

echo ""
echo "3. Checking configuration file..."
if [ -f "config.xml" ]; then
    echo "[INFO] Configuration file exists"
    echo "Current configuration:"
    cat config.xml
else
    echo "[WARNING] Configuration file not found"
fi

echo ""
echo "4. Instructions for testing resizable feature:"
echo "   - Move mouse to bottom-right corner of the clock"
echo "   - Cursor should change to diagonal resize arrow"
echo "   - Click and drag to resize"
echo "   - Release mouse to save new size"
echo "   - Size will be saved to config.xml"
echo ""
echo "5. To stop the application:"
echo "   - Right-click on clock and select 'Quit'"
echo "   - Or run: kill $PID"
echo ""
echo "Test the resizable feature now!"
echo "Press any key to continue..."
read -n 1 -s

echo ""
echo "6. Checking final configuration..."
if [ -f "config.xml" ]; then
    echo "Final configuration:"
    cat config.xml
else
    echo "Configuration file not found"
fi

echo ""
echo "Test completed!"
