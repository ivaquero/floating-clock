# GitHub Actions Build System

This project uses GitHub Actions for automated building and releasing across multiple platforms.

## Available Workflows

### 1. CI Build (`ci.yml`)

**Trigger**: Push to main/master branches, pull requests
**Purpose**: Quick validation builds on all platforms
**Artifacts**: Platform-specific executables

### 2. Build Qt (`build.yml`)

**Trigger**: Push to main/master branches, pull requests, manual dispatch
**Purpose**: Comprehensive builds using both qmake and CMake
**Artifacts**:

- qmake builds for each platform
- CMake builds for each platform

### 3. Release (`release.yml`)

**Trigger**: Git tags (v*), manual dispatch
**Purpose**: Create official releases with distributable packages
**Artifacts**:

- macOS: DMG installer
- Windows: ZIP package with dependencies
- Linux: TAR.GZ package

## Usage

### Automatic Builds

Every push to main/master branches triggers CI builds to ensure code quality.

### Creating a Release

1. Create and push a version tag:

   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```

2. The release workflow will automatically:
   - Build for all platforms
   - Create distributable packages
   - Create a GitHub release with artifacts

### Manual Release

1. Go to Actions tab in GitHub
2. Select "Build and Release Clouck"
3. Click "Run workflow"
4. Enter version number (e.g., v1.0.0)
5. Click "Run workflow"

## Build Requirements

### macOS

- Qt 6.5.0
- Xcode Command Line Tools
- macdeployqt for app bundling

### Windows

- Qt 6.5.0
- Visual Studio Build Tools or MinGW
- windeployqt for dependency deployment

### Linux

- Qt 6.5.0
- GCC/Clang
- X11 development libraries
- XFixes development libraries

## Artifacts

Each workflow produces platform-specific artifacts:

- **macOS**: `.app` bundle or `.dmg` installer
- **Windows**: Executable with Qt dependencies
- **Linux**: Executable with shared libraries

## Configuration

The workflows use:

- `jurplel/install-qt-action@v4` for Qt installation
- Matrix builds for multi-platform support
- Artifact upload for build retention
- Automatic release creation for tagged builds

## Troubleshooting

### Build Failures

1. Check Qt version compatibility
2. Verify platform-specific dependencies
3. Review build logs in GitHub Actions

### Missing Dependencies

- Ensure all required Qt modules are specified
- Check platform-specific library installations
- Verify CMake/qmake configuration

### Release Issues

- Ensure proper version tagging format (v*)
- Check GitHub token permissions
- Verify artifact upload paths
