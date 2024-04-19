#!/bin/bash
# Copyright (c) 2022 FirstBuild

if [ "$OSTYPE" == "darwin20" ]
then
   SERIAL_PORT='/dev/tty.usbmodem'
   STTY='stty -f'
elif [ "$OSTYPE" == "linux-gnueabihf" ]
then
   SERIAL_PORT='/dev/ttyACM'
   STTY='stty -F'
fi
SCRIPTS_DIR="$(dirname "$(realpath $0)")"
RELEASE="Mella_v1,0,2"

while [ true ]
do
   # read -n 1 -p "Connect the USB cable and press any key to attempt to FLASH a Mella board or press CTRL+C to exit "
   # zenity --warning --center  --width="500" --height="250" --title="CHECK USB CONNECTION" --text="Ensure USB is connected, then click OK to proceed"

   while [ `ls $SERIAL_PORT* 2>/dev/null | wc -l` -ne 1 ]
   do
      if [ `ls $SERIAL_PORT* 2>/dev/null | wc -l` -gt 1 ]
      then
         echo "Too many boards connected. Please only connect one board at a time."
         sleep 1
         # read -p "Connect the USB cable and press any key to attempt to FLASH a Mella board or press CTRL+C to exit. "
         zenity --warning --center --width="500" --height="250" --title="MULTIPLE BOARDS CONNECTED" --text="Please connect only one board at a time."
         exit 1
      elif [ `ls $SERIAL_PORT* 2>/dev/null | wc -l` -lt 1 ]
      then
         echo ""
         echo "No board detected."\n
         sleep 1
         echo ""
         # read -p "Connect the USB cable and press any key to attempt to FLASH a Mella board or press CTRL+C to exit. "
         zenity --warning --center --width="500" --height="250" --title="NO BOARD DETECTED" --text="Please connect a Mella board."
         exit 1
      fi
   done

   echo "Resetting board..."
   $STTY "$(ls $SERIAL_PORT*)" 1200
   while :; do
      sleep 0.5
      [ -c "$(ls $SERIAL_PORT*)" ] && break
   done
   avrdude -C "$SCRIPTS_DIR/avrdude.conf" -p atmega32u4 -P $(ls $SERIAL_PORT*) -c avr109 -b 57600 -v -D -Uflash:w:"$SCRIPTS_DIR/releases/$RELEASE.hex"

   if [ $? -ne 0 ]
   then
      echo "Failed flashing application. Please review output for details."
      exit 1
      sleep 2
   else
      echo "Successfully flashed Mella application"
      exit 0
      sleep 2
   fi
done
