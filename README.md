# LibCore - Custom C Library

## Overview

**LibCore** is an ever-expanding library of custom C functions designed for modularity and reuse across various projects. It serves as a personal toolkit, growing with each new project needs.

## File Structure

The project is organized to support modular development. New categories of functions can be added as subdirectories in `srcs`.

```
/
├── Makefile      # Build configuration
├── includes/     # Header files
├── srcs/
│   ├── core/     # Core standard library functions (strings, memory, etc.)
│   ├── list/     # Linked list implementations
│   └── [module]/ # Future modules
└── tests/        # Test suites matching the source modules
```

## Usage

### Compilation

Use the `make` command to compile specific modules or the entire library.

- **Compile Core only** (Default):
  ```bash
  make
  # OR
  make core
  ```
- **Compile Core + List**:
  ```bash
  make list
  ```
- **Compile All Modules**:
  ```bash
  make all
  ```

### Testing

Each module has a corresponding test target. Running a test target will compile the library and the tests, then execute them.

- **Run Core Tests**:
  ```bash
  make test
  # OR
  make test_core
  ```
- **Run List (and Core) Tests**:
  ```bash
  make tests_list
  ```
- **Run All Tests**:
  ```bash
  make tests_all
  ```

### Cleaning

By default, build artifacts are stored in a `tmp/` directory.

- **Remove object files and temporary directory**:
  ```bash
  make clean
  ```
- **Remove everything including the library (`libcore.a`)**:
  ```bash
  make fclean
  ```

### Integration

To use this library in another project:
1. Copy or submodule this repository.
2. Build the library: `make all`.
3. Link `libcore.a` and include the `includes/` directory in your project's build settings.
