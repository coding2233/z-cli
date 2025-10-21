# GEMINI.md

## Gemini CLI Development Guidelines for `z-cli`:

1.  **Project Context:**
    *   Always refer to `GEMINI.md` for the project overview, build process, and general development conventions.
    *   Prioritize `xmake.lua` files to understand project structure, dependencies, and build configurations.
    *   Analyze existing C++ source files (`.cpp`, `.h`) to infer coding style, architectural patterns, and common utility usage.

2.  **Code Modification:**
    *   **Style Adherence:** Strictly follow the established C++ coding style (indentation, brace style, naming) observed in the `z-cli` codebase.
    *   **Dependency Management:** Utilize only libraries already integrated via `xmake.lua` or explicitly documented in `GEMINI.md` (e.g., `spdlog`, `vfspp`, `xlnt`, `llama.cpp`). Avoid introducing new external dependencies without explicit user approval.
    *   **New Command Implementation:** When adding new commands, adhere to the `Cli` class inheritance pattern, implement the `Run` method, and ensure registration in `CliApp::AddClis()` as outlined in `GEMINI.md`.
    *   **Testing & Verification:** For new features or bug fixes, prioritize functional verification by running `xmake` and then executing relevant `z-cli` commands (e.g., `xmake run z-cli [command] --help`). If a testing framework is identified, I will propose or implement unit tests.
    *   **File System Interaction:** Within application logic, use `CliCore::GetCliCore().GetVirtualFileSystem()` for all file operations.

3.  **Build and Quality Assurance:**
    *   **Post-Modification Build:** After any code change, always attempt a full project build using `xmake`.
    *   **Functional Check:** Upon successful build, verify the changes by running the affected `z-cli` commands.
    *   **Error Resolution:** Upon build failures, I will analyze compiler output and correct the code accordingly.

4.  **Commit Practices:**
    *   When requested to commit, I will craft clear, concise, and informative commit messages that explain the *rationale* behind the changes, not just the superficial modifications.

5.  **User Interaction:**
    *   I will clearly articulate my plan before initiating significant code modifications.
    *   I will report the outcomes of all build and verification steps.
    *   I will seek explicit user confirmation for any potentially destructive or large-scale changes.