# Use Nushell as the lingua franca.
set shell := ['nu', '--commands']

build_dir := absolute_path('.build')

# Generate build system files into `.build/` via CMake.
config:
    @cmake --preset=default .

# Build all targets in the `.build/` folder via CMake.
build config='Debug':
    @cmake --build '{{ build_dir }}' --config '{{ config }}'

# Run the built binary.
run target:
    @^'{{ build_dir / target }}'

# Lint the code with Clang Tidy.
lint:
    @clang-tidy -p '{{ build_dir }}' ...(glob 'src/*.c')

# Format the code with Clang Format.
format:
    @clang-format -i ...(glob 'src/*.c')
