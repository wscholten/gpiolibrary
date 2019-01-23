# gpiolibrary

This is an experimental GPIO library for the UPboard. It relies on the 4.15 kernel which uses a different GPIO pin numbering.  The GPIO numbering matches that of the UP^2 board.

The header file gpiopin.h has the namiong setup for the GPIO pins matching the RPI naming BCM# and mapped to the kernel linux numbering.  For example BCM4 is linux 433 and is physical pin 7 on the header.

The gpilib.c contains the following core functions:

GPIOExport()    -- export the GPIO pin for use
GPIOUnexport()  -- unexport (free) the GPIO pin
GPIODirection() -- set the direction of the GPIO pin (IN or OUT)
GPIORead()      -- read the GPIO pin - expect an input
GPIOWrite()     -- write to a GPIO pin

The gpiodemo.c program demonstrates how to use the basic functions.

In order for this library to work, a set of UDEV rules are required, allowing GPIO pin access as a none elevated user (none sudo)

To compile the sample use:  gcc -o bin/gpiodemo -I include gpiodemo.c gpiolib.c
then run the program using: ./bin/gpiodemo
