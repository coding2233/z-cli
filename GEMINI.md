# GEMINI.md

## Project Overview

This project, `z-cli`, is a C++ command-line interface (CLI) application. It provides a shell-like interface for various sub-commands and can also be used to execute single commands directly. The project is built using the `xmake` build system.

The application is designed to be extensible, with a clear pattern for adding new commands. Currently, it includes commands for interacting with Excel files (`excel`), updating the application (`update`), translation (`fy`), and handling JSON (`json`).

Key technologies and libraries used:
*   **C++17**
*   **xmake** for building
*   **spdlog** for logging
*   A custom virtual file system (`vfspp`) for file operations.
*   Dependencies such as `xlnt` and `llama.cpp` are managed through `xmake`.

## Building and Running

The project is built and run using `xmake`.

*   **Build the project:**
    ```bash
    xmake
    ```

*   **Run the application in interactive mode:**
    ```bash
    xmake run z-cli
    ```
    This will start the `z-cli>` shell.

*   **Run a specific command:**
    ```bash
    xmake run z-cli [command] [args...]
    ```
    For example:
    ```bash
    xmake run z-cli excel --help
    ```

*   **Clean the build:**
    ```bash
    xmake clean
    ```

## Development Conventions

*   **Adding New Commands:** To add a new command, you need to:
    1.  Create a new class that inherits from the `Cli` class.
    2.  Implement the `Run` method for your new command.
    3.  Register the new command in `CliApp::AddClis()` in `src/cli_app.cpp`.
*   **File System:** The application uses a virtual file system. Use the `CliCore::GetCliCore().GetVirtualFileSystem()` to interact with files.
*   **Logging:** Use the `spdlog` library for logging.
