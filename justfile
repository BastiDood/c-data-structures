# Use Nushell as the lingua franca.
set shell := ['nu', '--commands']

BUILD_DIR := absolute_path('.build')

# Generate build system files into `.build/` via CMake.
config:
    @cmake --preset=default -B '{{ BUILD_DIR }}' .

# Build all targets in the `.build/` folder via CMake.
build config='Debug':
    @cmake --build '{{ BUILD_DIR }}' --config '{{ config }}'

# Run the built binary.
run target:
    @^'{{ BUILD_DIR / target }}'

# Lint the code with Clang Tidy.
lint:
    @clang-tidy -p '{{ BUILD_DIR }}' ...(glob 'src/*.c')

# Format the code with Clang Format.
format:
    @clang-format -i ...(glob 'src/*.c')
