set shell := ['nu', '--commands']

BUILD_DIR := '.build'
SOURCE_FILES_GLOB := 'src/**/*.{c,h}'

all: fmt config lint test

# Generate build system files into `.build/` via CMake.
config:
    cmake --preset=default -B '{{ BUILD_DIR }}' .

# Build all targets in the `.build/` folder via CMake.
build config='Debug':
    cmake --build '{{ BUILD_DIR }}' --config '{{ config }}'

# Run the unit tests for the given configuration.
test config='Debug': (build config)
    ctest --preset=default --build-config '{{ config }}'

# Lint the code with Clang Tidy.
lint:
    clang-tidy --quiet -p '{{ BUILD_DIR }}' ...(glob '{{ SOURCE_FILES_GLOB }}')

# Apply lint fix suggestions from Clang Tidy.
fix-lint:
    clang-tidy --quiet --fix -p '{{ BUILD_DIR }}' ...(glob '{{ SOURCE_FILES_GLOB }}')

# Check code formatting with Clang Format.
fmt:
    clang-format --dry-run ...(glob '{{ SOURCE_FILES_GLOB }}')

# Fix code formatting with Clang Format.
fix-fmt:
    clang-format -i ...(glob '{{ SOURCE_FILES_GLOB }}')
