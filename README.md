# Basic Data Structures in C

This repository contains reference implementations for various basic data structures in C. The public interfaces are intentionally incomplete to encourage the reader to fill in the blanks and implement their own extensions.

* [Singly-Linked List](./src/singly.c)
* [Doubly-Linked List](./src/doubly.c)

## Running the Code

This project uses the [CMake] (v3.30+) build system generator for cross-platform builds. I personally prefer the multi-configuration [Ninja] build system, but feel free to use your system's default (e.g., Microsoft Visual Studio Compiler, Xcode, and Make).

[CMake]: https://cmake.org/
[Ninja]: https://ninja-build.org/

The [Just] (v1.35+) task runner for convenience. However, it is totally possible to run the commands yourself. Consult the [`justfile`] for more details on the raw commands being executed.

[Just]: https://just.systems/
[`justfile`]: ./justfile

```bash
# Generate the build system configurations in `.build/`
just config

# Build all targets in debug mode
just

# Build all targets in release mode (if supported by the generator)
just build Release

# Convenience aliases for running the built binaries
just run singly
just run doubly
```
