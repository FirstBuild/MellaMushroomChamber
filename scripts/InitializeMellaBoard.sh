#!/bin/bash
# Copyright (c) 2022 FirstBuild

SCRIPTS_DIR="$(dirname $(realpath $0))"
# avrdude -C "$SCRIPTS_DIR/avrdude.conf" -p atmega32u4 -P usb -c avrispmkII -v -Ulock:w:0x3F:m -U lfuse:w:0xFF:m -U hfuse:w:0xDA:m -U efuse:w:0xCB:m
avrdude -C "$SCRIPTS_DIR/avrdude.conf" -p atmega32u4 -P usb -c avrispmkII -v -Ulock:w:0xFF:m -U lfuse:w:0xE2:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m

if [ $? -ne 0 ]
then
   echo "Failed writing fuses. Please review output for details."
   exit 1
else
   echo "Successfully set fuses. Now flashing bootloader..."
   sleep 2
   # avrdude -C "$SCRIPTS_DIR/avrdude.conf" -p atmega32u4 -P usb -c avrispmkII -v -U flash:w:"$SCRIPTS_DIR/Caterina-Leonardo.hex"
   avrdude -C "$SCRIPTS_DIR/avrdude.conf" -p atmega32u4 -P usb -c avrispmkII -v -U flash:w:"$SCRIPTS_DIR/Caterina-Flora8.hex"

   if [ $? -ne 0 ]
   then
      echo "Failed flashing bootloader. Please review output for details."
      exit 1
   else
      echo "Successfully wrote bootloader!"
      exit 0
   fi
fi
