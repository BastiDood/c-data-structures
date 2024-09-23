default: build

config:
    @cmake --preset=default .

build config='Debug':
    @cmake --build .build --config {{config}}

run target:
    @.build/{{target}}.exe
