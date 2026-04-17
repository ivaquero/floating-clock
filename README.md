# ⏰ Flock

![code size](https://img.shields.io/github/languages/code-size/ivaquero/floating-clock.svg)
![repo size](https://img.shields.io/github/repo-size/ivaquero/floating-clock.svg)

This project aims to build a cross-platform floating clock based on Qt6.

## Motivation

When coding in full screen mode, I often forget the time.
When on macOS / Linux, the clock on the menu bar is too small to be noticeable, so is the clock on Windows.

![clock](doc/clock.png)

## ✨ Features

- [ ] **Main Window**
  - [ ] Frameless
  - [x] Drag and Move
  - [x] Right Click Menu
  - [ ] Always On Top
  - [ ] Show in Fullscreen Mode
- [x] **Style**
  - [x] Set Background Color
  - [x] Set Font Color
  - [x] Set FontSize
- [ ] **Configuration File** (XML)
  - [ ] Read Settings
  - [ ] Write Settings
  - [ ] Reset Settings
- [ ] **Time**
  - [ ] Select Time Zone
  - [ ] Set Alarms

## Quick Start

### Build and Run

#### Quick Build (Recommended)

```bash
# One-click build
./build.sh

# Run application
./build/flock.app/Contents/MacOS/flock  # macOS
./build/flock                           # Linux
```

#### Manual Build

```bash
# Clean build files
./clean.sh

# Generate Makefile
qmake flock.pro

# Build
make

# Run
./build/flock.app/Contents/MacOS/flock  # macOS
./build/flock                             # Linux
```

#### Using CMake

```bash
mkdir build && cd build
cmake ..
make
./flock
```

### Usage

- **Move**: Left-click and drag
- **Menu**: Right-click for context menu
- **Customize**: Change colors, font size, always-on-top behavior

### Project Structure

```text
qflock/
├── build/                    # Build output directory
│   ├── flock.app/           # macOS application bundle
│   ├── *.o                   # Object files
│   ├── moc_*.cpp            # Qt meta-object compiler output
│   └── Makefile             # Build file
├── build.sh                 # One-click build script
├── clean.sh                 # Clean script
├── flock.pro                # qmake project file
├── CMakeLists.txt           # CMake project file
└── README.md
```

### Build Output Management

- All compilation files (.o, moc_*.cpp, Makefile, etc.) are output to `build/` directory
- Executable files are located at `build/flock.app/Contents/MacOS/flock` (macOS) or `build/flock` (Linux)
- Use `./clean.sh` to quickly clean all build files
- Use `./build.sh` for complete one-click build

### Next Steps

- Time zone selection
- Alarm functionality
- Enhanced UI/UX

## Requirements

- Qt6 (Core, Widgets)
- C++17 compatible compiler
- CMake 3.16+ (optional, for CMake build)

## License

See LICENSE file for details.
