# C++ Project Template (CMake)

A **simple, modern, and extendable C++ project template** using **CMake**.  
Designed to stay minimal for small projects, while scaling cleanly as the codebase grows.

This template focuses on:
- Clear project structure
- Target-based CMake (no global flags abuse)
- Easy build/debug workflows
- Room to grow (libraries, tests, vendors, multiple apps)

---

## Requirements

- **CMake ≥ 3.22**
- **C++20 compatible compiler**
  - GCC / Clang / MSVC
- Unix Makefiles (default generator)

---

## Project Structure

```
myproj/
  CMakeLists.txt
  CMakePresets.json
  cmake/
    options.cmake
    warnings.cmake
  src/
    CMakeLists.txt
    main.cpp
  include/
    myproj/
      version.h.in
  tests/
    CMakeLists.txt
    smoke_test.cpp
  build/                 # generated (gitignored)
```

### Directory purpose

| Directory | Purpose |
|---------|--------|
| `src/` | Application entry point(s) |
| `include/` | Public headers |
| `cmake/` | Reusable CMake helpers (warnings, options, etc.) |
| `tests/` | Executable-based tests |
| `build/` | Out-of-source build artifacts |

---

## Building the Project

This template uses **CMake Presets** for a simple workflow.

### Configure

```bash
cmake --preset debug
```

### Build

```bash
cmake --build --preset debug
```

### Run

```bash
./build/debug/src/myproj
```

---

## Build Presets

Two presets are provided:

| Preset | Description |
|------|------------|
| `debug` | Debug symbols, assertions enabled |
| `release` | Optimized build |

Switching presets:

```bash
cmake --preset release
cmake --build --preset release
```

---

## Running Tests

Tests are enabled by default.

```bash
ctest --test-dir build/debug
```

Disable tests if needed:

```bash
cmake --preset debug -DMYPROJ_BUILD_TESTS=OFF
```

---

## Configuration Options

Available CMake options:

| Option | Description | Default |
|------|------------|---------|
| `MYPROJ_BUILD_TESTS` | Build test targets | `ON` |
| `MYPROJ_WARNINGS_AS_ERRORS` | Treat warnings as errors | `OFF` |

Example:

```bash
cmake --preset debug -DMYPROJ_WARNINGS_AS_ERRORS=ON
```

---

## Version Header

A version header is generated automatically at build time:

```cpp
#include "myproj/version.h"
```

```cpp
#define MYPROJ_VERSION "0.1.0"
```

This version comes from the `project()` declaration in the root `CMakeLists.txt`.

---

## Extending the Template

### Adding a library

Recommended pattern:

```cmake
add_library(myproj_core
  foo.cpp
  bar.cpp
)

target_include_directories(myproj_core PUBLIC include)
```

Then link it:

```cmake
target_link_libraries(myproj PRIVATE myproj_core)
```

### Adding more executables

Create a new subdirectory (e.g. `app/`) and add another `add_executable()`.

### Adding dependencies

- **System libraries:** `find_package()`
- **Header-only / bundled:** `vendor/`
- **Fetched deps:** `FetchContent`

All integrate cleanly with the target-based design.

---

## Tooling Support

- `compile_commands.json` is generated automatically
  - Works with **clangd**, **Neovim**, **VS Code**
- Out-of-source builds keep the repo clean
- No generator lock-in (Ninja optional but not required)

---

## Philosophy

This template intentionally avoids:
- Over-engineering
- Hidden magic
- Monolithic `CMakeLists.txt`

Instead, it provides:
- Clear separation of concerns
- Predictable build behavior
- Easy customization

---

## License

Use this template however you like.  
No restrictions.
