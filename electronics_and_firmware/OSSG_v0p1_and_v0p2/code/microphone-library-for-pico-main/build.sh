#!/usr/bin/env bash

export PICO_SDK_PATH=/home/cayden/programs/pico-sdk
rm -rf build
mkdir build
cd build
cmake .. -DPICO_BOARD=pico
make
echo "To convert from elf to uf2:"
echo "./elf2uf2/elf2uf2 examples/usb_microphone/usb_microphone.elf usb_microphone_gpio25.uf2"
./elf2uf2/elf2uf2 ./examples/usb_microphone/usb_microphone.elf ./usb_mic_with_slaves.uf2
cp usb_mic_with_slaves.uf2 ~/flasher
