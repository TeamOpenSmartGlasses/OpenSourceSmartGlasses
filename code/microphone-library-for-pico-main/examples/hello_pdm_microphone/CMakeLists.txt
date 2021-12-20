cmake_minimum_required(VERSION 3.12)

# rest of your project
add_executable(hello_pdm_microphone
    main.c
)

target_link_libraries(hello_pdm_microphone pico_pdm_microphone)

# enable usb output, disable uart output
pico_enable_stdio_usb(hello_pdm_microphone 1)
pico_enable_stdio_uart(hello_pdm_microphone 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello_pdm_microphone)
