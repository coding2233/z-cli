# z-cli 项目文档

## 项目概述

z-cli 是一个基于 C++17 开发的命令行工具集合，提供多种实用功能模块。该项目采用模块化架构设计，使用 xmake 作为构建系统，支持跨平台编译。

### 主要特性

- **模块化设计**：每个功能作为独立的 CLI 模块实现
- **统一接口**：所有模块继承自 `Cli` 基类，提供一致的命令行接口
- **虚拟文件系统**：集成 vfspp 库，提供统一的文件系统抽象
- **国际化支持**：内置 UTF-8 处理和翻译功能
- **日志系统**：集成 spdlog 库提供强大的日志功能

## 技术栈

- **编程语言**：C++17, C17
- **构建系统**：xmake
- **核心依赖**：
  - spdlog (日志)
  - vfspp (虚拟文件系统)
  - libcurl (网络请求)
  - cxxopts (命令行选项解析)
  - xlnt (Excel 文件操作)
  - utf8cpp (UTF-8 处理)

## 项目结构

```
z-cli/
├── src/
│   ├── main.cpp              # 程序入口
│   ├── cli_app.h/cpp         # CLI 应用程序主类
│   ├── cli.h                 # CLI 基类定义
│   ├── core/                 # 核心功能模块
│   │   ├── cli_core.h/cpp    # 核心功能实现
│   │   ├── spdlog-1.15.3/    # 日志库
│   │   ├── vfspp/            # 虚拟文件系统
│   │   ├── utf8cpp/          # UTF-8 处理库
│   │   └── json/             # JSON 处理库
│   ├── excel/                # Excel 操作模块
│   │   ├── excel_cli.h/cpp   # Excel CLI 实现
│   │   └── xmake.lua         # Excel 模块构建配置
│   ├── fanyi/                # 翻译模块
│   │   ├── fanyi_cli.h/cpp   # 翻译 CLI 实现
│   │   └── xmake.lua         # 翻译模块构建配置
│   ├── json/                 # JSON 操作模块
│   │   ├── json_cli.h/cpp    # JSON CLI 实现
│   │   └── xmake.lua         # JSON 模块构建配置
│   ├── update/               # 更新模块
│   │   ├── update_cli.h/cpp  # 更新 CLI 实现
│   │   └── xmake.lua         # 更新模块构建配置
│   └── generated/            # 自动生成的文件
│       └── add_clis.cpp      # CLI 注册代码
├── xmake/                    # xmake 插件
│   └── plugins/
│       └── gen_add_clis/     # 自动生成 CLI 注册代码的插件
├── my-repositories/          # 本地包仓库
└── build/                    # 构建输出目录
```

## 构建和运行

### 环境要求

- C++17 兼容的编译器
- xmake 构建系统
- curl 开发库

### 构建命令

```bash
# 构建项目
xmake

# 运行程序
xmake run z-cli

# 运行特定命令
xmake run z-cli excel --help
xmake run z-cli fanyi --help
xmake run z-cli json --help
xmake run z-cli update --help
```

### 清理构建

```bash
# 清理构建文件
xmake clean

# 清理所有
xmake clean --all
```

## 可用命令

### Excel 操作 (excel)

提供 Excel 文件的读取和处理功能。

### 翻译工具 (fanyi)

提供文本翻译功能，支持多种语言。

### JSON 工具 (json)

提供 JSON 文件的格式化和处理功能。

### 更新工具 (update)

提供应用程序和组件的更新功能。

## 开发指南

### 添加新命令

1. 在 `src/` 下创建新的模块目录（如 `src/newcmd/`）
2. 创建命令类继承自 `Cli` 基类：
   ```cpp
   class NewCmdCli : public Cli
   {
   public:
       NewCmdCli(std::string name) : Cli(name, "Command description") {}
       void SetupOptions() override;
       bool Run(cxxopts::ParseResult result) override;
   };
   ```
3. 实现 `SetupOptions()` 和 `Run()` 方法
4. 创建模块的 `xmake.lua` 配置文件
5. 在根目录 `xmake.lua` 中添加模块引用
6. 运行 `xmake` 重新构建，`add_clis.cpp` 会自动更新

### 代码规范

- 使用 C++17 标准
- 遵循现有代码的命名约定和格式
- 所有文件操作使用 `CliCore::GetCliCore().GetVirtualFileSystem()`
- 使用 spdlog 进行日志记录
- 错误处理使用适当的返回值和异常机制

### 文件系统操作

项目使用虚拟文件系统抽象，所有文件操作应通过以下方式：

```cpp
auto& core = CliCore::GetCliCore();
auto vfs = core.GetVirtualFileSystem();
// 使用 VFS API 进行文件操作
```

## 依赖管理

项目使用 xmake 的包管理系统管理依赖：

- 核心依赖在 `src/core/xmake.lua` 中定义
- 模块特定依赖在各模块的 `xmake.lua` 中定义
- 本地包存储在 `my-repositories/` 目录

## 调试和测试

### 调试模式

```bash
# 以调试模式构建
xmake f -m debug
xmake
```

### 功能验证

修改代码后，建议按以下步骤验证：

1. 构建项目：`xmake`
2. 运行相关命令：`xmake run z-cli [command] --help`
3. 测试具体功能

## 自动化工具

项目包含自动化插件 `gen_add_clis`，用于自动生成 CLI 注册代码，确保新添加的命令模块自动集成到主应用程序中。

## 版本信息

当前版本：1.0.0 (定义在 `CLI_APP_VERSION` 宏中)