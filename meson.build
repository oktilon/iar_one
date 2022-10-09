project('iar_one', 'c')
version = [1, 0, 0]

# https://github.com/hwengineer/STM32F3Discovery-meson-example

# Includes and sources
inc = [
      include_directories('Libraries/CMSIS/Include')
    , include_directories('Libraries/CMSIS/Device/ST/STM32F4xx/Include')
    , include_directories('Libraries/STM32F4xx_StdPeriph_Driver/inc')
    , include_directories('Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates')
    , include_directories('Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar')
    , include_directories('Libraries/STM32F4xx_StdPeriph_Driver/src')
    , include_directories('Application/inc')
    , include_directories('Application/src')
    , include_directories('Application')
]

src = [
      'Application/src/board.c'
    , 'Application/src/dac.c'
    , 'Application/src/task.c'
    , 'Application/main.c'
]

# Dependencies
# deps = [
#     dependency('libsystemd')
# ]

# Create executable
main = executable(
    'main',
    sources : src,
    include_directories : inc,
    name_suffix : 'elf',
    c_args: [c_args],
    link_args : [link_args, '-Wl,--gc-sections'],
    dependencies : deps
)

objcopy = '@0@'.format(find_program('objcopy').path())

mainbin = custom_target(
                        'main.bin',
    output           : ['main.bin'],
    # name_suffix      : 'bin',
    build_by_default : true,
    command          : [objcopy, '-O', 'binary', 'main.elf', 'main.bin'],
    depends          : [main]
)

mainhex = custom_target(
                        'main.hex',
    output           : ['main.hex'],
    build_by_default : true,
    command          : [objcopy, '-O', 'ihex', 'main.elf', 'main.hex'],
    depends          : [main]
)