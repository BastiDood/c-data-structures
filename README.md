# Basic Data Structures in C

This repository contains reference implementations for various basic data structures in C. The public interfaces are intentionally incomplete to encourage the reader to fill in the blanks and implement their own extensions.

* [Slice](./src/slice/)
* [Stack](./src/stack/)
* [Queue](./src/queue/)
* [Binary Heap](./src/binary-heap/)
* [Singly-Linked List](./src/singly-linked-list/)
* [Doubly-Linked List](./src/doubly-linked-list/)

## Running the Code

This project uses the [CMake] (v3.30+) build system generator for cross-platform builds. I personally prefer the multi-configuration [Ninja] (v1.12+) build system, but feel free to use your system's default (e.g., Microsoft Visual Studio Compiler, Xcode, and Make).

[CMake]: https://cmake.org/
[Ninja]: https://ninja-build.org/

For convenience and widest compatibility, we use the [Just] (v1.35+) task runner with the cross-platform [Nushell] (v0.97+) shell to run common commands. However, it is totally possible to run the raw commands yourself. Consult the [`justfile`] for more details.

[Just]: https://just.systems/
[Nushell]: https://www.nushell.sh/
[`justfile`]: ./justfile

```bash
# Generate the build system configurations in `.build/`
just config

# Build all targets in debug mode
just build

# Build all targets in release mode (if supported by the generator)
just build Release

# Run all unit tests
just test
```

## Linting the Codebase

```bash
# Run Clang Format as the formatter.
just fmt     # check
just fix-fmt # fix

# Run Clang Tidy as the linter.
just lint     # check
just fix-lint # fix
```
