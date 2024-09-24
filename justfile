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
    glob '{{ SOURCE_FILES_GLOB }}' | par-each { |path| { file: ($path | path relative-to (pwd)), output: (clang-tidy --quiet -p '{{ BUILD_DIR }}' $path e>| lines) } } | where ($it.output | is-not-empty) | update output { |row| $row.output | str join "\n" }

# Apply lint fix suggestions from Clang Tidy.
fix-lint:
    glob '{{ SOURCE_FILES_GLOB }}' | par-each { |path| { file: ($path | path relative-to (pwd)), output: (clang-tidy --quiet --fix -p '{{ BUILD_DIR }}' $path e>| lines) } } | where ($it.output | is-not-empty) | update output { |row| $row.output | str join "\n" }

# Check code formatting with Clang Format.
fmt:
    glob '{{ SOURCE_FILES_GLOB }}' | par-each { |path| clang-format --dry-run $path } | ignore

# Fix code formatting with Clang Format.
fix-fmt:
    glob '{{ SOURCE_FILES_GLOB }}' | par-each { |path| clang-format -i $path } | ignore
