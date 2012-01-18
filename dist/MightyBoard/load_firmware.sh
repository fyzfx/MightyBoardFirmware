#!/bin/bash

    echo "Press ENTER to upload 8U2 Firmware"
    read
    # Upload bootloader via isp
    avrdude -p at90usb82 -F -P usb -c usbtiny -U flash:w:Makerbot-usbserial.hex -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xF4:m -U lock:w:0x0F:m

    echo "Press ENTER to upload 1280 Firmware"
    read
    # Upload bootloader via isp
    avrdude -p m1280 -F -P usb -c avrispmkii -U flash:w:MightyBoard.hex -U lfuse:w:0xFF:m -U hfuse:w:0xDA:m -U efuse:w:0xF4:m -U lock:w:0x0F:m

    echo "Press ENTER to test USB"
    read
    # Upload bootloader via isp
    avrdude -F -V -p m1280 -P /dev/ttyACM0 -c stk500v1 -b 57600 -U flash:w:build/mb40/MightyBoard.hex



#!/bin/bash



