#!/bin/bash
# Copyright (c) 2022 FirstBuild

SCRIPTS_DIR="$(dirname $(realpath $0))"

function FlashMella {

    bash "$SCRIPTS_DIR/FlashMella.sh"
    if [ $? -eq 0 ]
    then
        zenity --question --icon-name=info --width="500" --height="250" --text '<span font="18">Successfully flashed Mella application</span>' \
        --title="FLASHING COMPLETE" --ok-label="Verify" --cancel-label="Exit"
        if [ $? -eq 1 ]
        then
            exit
        else
            Verify
        fi
    else
        zenity --warning --width="300" --height="250" --title="FLASHING ERROR" --text '<span font="18">Failed to flash Mella. Check connections, then click OK to try again.</span>'
        if [ $? -eq 0 ]
        then
            FlashMella
        fi
    fi
}

function WriteBootloader {
    bash "$SCRIPTS_DIR/InitializeMellaBoard.sh"
    if [ $? -eq 0 ]
    then
        zenity --info --width="500" --height="250" --title="Success" --text '<span font="18">Successfully wrote bootloader. Click OK to flash software.</span>'
        if [ $? -eq 0 ]
        then
            FlashMella
        fi
    else
        zenity --warning --width="500" --height="250" --title="BOOTLOADER WRITE FAILURE" --text '<span font="18">There was a problem writing the bootloader. Check your connections and try again.</span>'
        if [ $? -eq 0 ]
        then
            WriteBootloader
        else
            return
        fi
    fi
}

function Verify {
    bash "$SCRIPTS_DIR/Verify.sh"
    return
}

while [ true ]
do
    ans=$(zenity --list --title="Mella2.0 Flasher" --text '<span font="24">Please select an option:</span>' --column="Options" --cancel-label="Exit" --width="500" --height="250" \
    "Flash Software" "Verify")
    if [ "$ans" = "Flash Software" ]
    then
        zenity --warning --width="500" --height="250" --title="CONNECT YOUR BOARD" --text '<span font="18">Connect programming header, then click OK to proceed </span>'
        if [ $? -eq 0 ]
        then
            WriteBootloader
        fi
    elif [ "$ans" = "Verify" ]
    then
        Verify
    else
        exit
    fi
done
