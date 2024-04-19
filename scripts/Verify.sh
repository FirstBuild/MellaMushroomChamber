#!/bin/bash
# Copyright (c) 2022 FirstBuild

if [ "$OSTYPE" == "darwin20" ]
then
   LOG_PORT='/dev/tty.usbmodem'
elif [ "$OSTYPE" == "linux-gnueabihf" ]
then
   LOG_PORT='/dev/ttyACM'
fi

function SuccessPrompt
{
   zenity --info --width="500" --height="250" --title="SUCCESS" \
   --text="<span font=\"24\" color=\"green\">Programming Complete! Remember to disconnect headers from unit.</span>"
   exit
}

function FailPrompt
{
   zenity --warning --width="500" --height="250" --title="TEST FAILED" \
   --text="<span font=\"24\" color=\"red\">TEST FAILED! EXITING...</span>"
   exit
}

function VerificationPrompt ()
{
   zenity --info --width="500" --height="250" --title="$1" \
   --text="<span font=\"18\">$2</span>"
   if [ $? -eq 1 ]
   then
      FailPrompt
   fi
   return
}

function GetLoggingData
{
   screen -S Logger -d -m -L $LOG_PORT* 9600
   sleep 3
   screen -XS Logger quit
   sleep 1
   grep '|,' screenlog.0 | tail -1 > log.txt
   rm screenlog.0
}

function GetVersionAndHumidity
{
   progressBar
   VERSION="$(rev log.txt | cut -d, -f-3 | rev | cut -d, -f1)"
   HUMIDITY="$(rev log.txt | cut -d, -f-14 | rev | cut -dR -f1)"
   rm log.txt
}

function progressBar
{
   (
   echo "10"; sleep 1
   echo "20" ; sleep 1
   echo "30" ; sleep 1
   echo "40" ; sleep 1
   echo "# This will take a few seconds..." ; sleep 1
   GetLoggingData
   echo "80" ; sleep 1
   echo "# Almost done..." ; sleep 1
   echo "# Complete!" ; sleep 1
   echo "100" ;
   ) |
   zenity --progress \
   --width="500" --height="250" \
   --title="GATHERING INFO" \
   --text="Reading..." \
   --percentage=0 \
   --auto-close
}

sleep 3
GetVersionAndHumidity
VerificationPrompt "VERSION CHECK" "Version:$VERSION\n Confirm this the correct version."
VerificationPrompt "HUMIDITY RANGE CHECK" "Humidity reading:$HUMIDITY\n Confirm this an acceptable value (30% - 70%)?"
SuccessPrompt
exit
