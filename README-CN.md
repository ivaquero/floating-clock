# QFlock - Qt6 浮动时钟

## 功能特性

✅ **已实现的功能：**

- **无边框窗口** - 简洁的浮动时钟界面
- **拖拽移动** - 鼠标左键拖拽移动窗口位置
- **右键菜单** - 丰富的自定义选项
- **总在最前** - 始终显示在其他窗口之上
- **透明背景** - 支持半透明背景效果
- **自定义样式** - 可调整字体颜色、背景颜色、字体大小
- **设置持久化** - 自动保存和恢复用户设置
- **跨平台支持** - 基于Qt6，支持macOS/Linux/Windows

## 使用方法

### 基本操作

- **移动时钟**：鼠标左键点击并拖拽
- **显示菜单**：右键点击时钟
- **退出应用**：右键菜单选择"退出"

### 自定义设置

- **字体颜色**：右键菜单 → 设置字体颜色
- **背景颜色**：右键菜单 → 设置背景颜色
- **字体大小**：右键菜单 → 设置字体大小
- **总在最前**：右键菜单 → 勾选/取消"总在最前"
- **重置设置**：右键菜单 → 重置设置

### 构建和运行

#### 快速构建（推荐）：

```bash
# 一键构建
./build.sh

# 运行应用
./build/flock.app/Contents/MacOS/flock  # macOS
./build/flock                           # Linux
```

#### 手动构建：

```bash
# 清理旧的构建文件
./clean.sh

# 生成Makefile
qmake flock.pro

# 编译
make

# 运行
./build/flock.app/Contents/MacOS/flock  # macOS
./build/flock                             # Linux
```

#### 使用CMake构建：

```bash
mkdir build && cd build
cmake ..
make
./flock
```

### 项目结构

```text
qflock/
├── build/                    # 构建输出目录
│   ├── flock.app/           # macOS应用包
│   ├── *.o                   # 目标文件
│   ├── moc_*.cpp            # Qt元对象编译器输出
│   └── Makefile             # 构建文件
├── src/                     # 源代码（建议）
├── build.sh                 # 一键构建脚本
├── clean.sh                 # 清理脚本
├── flock.pro                # qmake项目文件
├── CMakeLists.txt           # CMake项目文件
└── README.md
```

## 技术特点

- **Qt6框架**：使用最新的Qt6库
- **透明窗口**：支持RGBA透明背景
- **定时器更新**：每秒更新时钟显示
- **设置管理**：使用QSettings持久化用户偏好
- **事件处理**：自定义鼠标事件实现拖拽功能

## 开发说明

### 构建输出管理

- 所有编译生成的文件（.o, moc_*.cpp, Makefile等）都会输出到`build/`目录
- 可执行文件位于`build/flock.app/Contents/MacOS/flock`（macOS）或`build/flock`（Linux）
- 使用`./clean.sh`可以快速清理所有构建文件
- 使用`./build.sh`可以进行完整的一键构建

### 自定义构建配置

可以在`flock.pro`中修改以下配置：

- `DESTDIR`：可执行文件输出目录
- `OBJECTS_DIR`：目标文件输出目录
- `MOC_DIR`：元对象编译器输出目录

## 更新日志

### v1.0.0 (2026-04-18)

- ✨ 初始版本发布
- ✨ 基础时钟功能
- ✨ 拖拽移动支持
- ✨ 右键菜单功能
- ✨ 样式自定义
- ✨ 设置持久化
- ✨ 构建输出目录管理
