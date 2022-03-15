# rest of your project
add_executable(usb_microphone
    main.c
)

target_link_libraries(usb_microphone pico_stdlib pico_pdm_microphone)
#target_include_directories(usb_microphone PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Serial through USB
pico_enable_stdio_usb(usb_microphone 1)
pico_enable_stdio_uart(usb_microphone 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(usb_microphone)

