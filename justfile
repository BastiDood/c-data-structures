set shell := ['nu', '--commands']

BUILD_DIR := absolute_path('.build')

all: fmt config lint build

# Generate build system files into `.build/` via CMake.
config:
    cmake --preset=default -B '{{ BUILD_DIR }}' .

# Build all targets in the `.build/` folder via CMake.
build config='Debug':
    cmake --build '{{ BUILD_DIR }}' --config '{{ config }}'

# Run the built binary.
run target:
    ^'{{ BUILD_DIR / target }}'

# Lint the code with Clang Tidy.
lint:
    clang-tidy --quiet -p '{{ BUILD_DIR }}' ...(glob 'src/*.c')

# Apply lint fix suggestions from Clang Tidy.
fix-lint:
    clang-tidy --quiet --fix -p '{{ BUILD_DIR }}' ...(glob 'src/*.c')

# Check code formatting with Clang Format.
fmt:
    clang-format --dry-run ...(glob 'src/*.c')

# Fix code formatting with Clang Format.
fix-fmt:
    clang-format -i ...(glob 'src/*.c')
