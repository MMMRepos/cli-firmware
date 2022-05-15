# Firmware for Interacting with a Command Line Interface Application 

## Introduction
The firmware is written for interacting with a CLI application. The application can be written in any language (Python, Java, C#, etc.) but it should interact with the hardware using UART communication protocol.
The hex file for the firmware is available in this repository along with the source code.

#### Prerequisites
Following applications are required to make modifications to the existing firmware and compile it to create the new firmware image:
+ [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide) v5.50 or later
+ [XC8 Compiler](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers) v2.35 or later

### Hardware
+ The firmware is developed to run on [ATmega4809 Curiosity Nano Development Board](https://www.microchip.com/en-us/development-tool/DM320115).
+ The code is written in such a way that the CLI functionality can be ported to any other hardware of user's choice.

## Firmware Functionality
+ The cli.c and cli.h file are responsible for handling the command reception, processing and sending a response to the received command. These files form the core of the CLI firmware.
+ The firmware was tested using [CLI Application](https://github.com/MMMRepos/cli-python.git), a headless CLI application written in Python.

