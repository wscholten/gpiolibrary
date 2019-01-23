# gpiolibrary

This is an experimental GPIO library for the UPboard. It relies on the 4.15 kernel which uses a different GPIO pin numbering.  The GPIO numbering matches that of the UP^2 board.

The header file gpiopin.h has the naming setup for the GPIO pins matching the RPI naming BCM# and mapped to the kernel linux numbering.  For example BCM4 is linux 433 and is physical pin 7 on the header.

The header configgpio.h is used to setup which pins the program will use, and what direction the pin is set to. This is done through two simple arrays, where the index points to the PIN in one array and the direction in the other.

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

UDEV rules
==========

The following UDEV rules should be present in this directory:
/lib/udev/rules.d/

The UDEV rule file should be called: 99-gpio.rules

The rules in this file should be:

# rules to permit access to hat peripheral from userspace
SUBSYSTEM=="gpio", KERNEL=="gpio*",     GROUP:="gpio"     MODE:="0660"
SUBSYSTEM=="gpio", KERNEL=="gpiochip*", ACTION=="add", PROGRAM="/bin/sh -c 'chown root:gpio /sys/class/gpio/export /sys/classgpio/unexport ; chmod 220 /sys/class/gpio/export /sys/class/gpio/unexport'"
SUBSYSTEM=="gpio", KERNEL=="gpio*",     ACTION=="add", PROGRAM="/bin/sh -c 'chown root:gpio /sys%p/active_low /sys%p/direction sys%p/edge /sys%p/value ; chmod 660 /sys%p/active_low /sys%p/direction /sys%p/edge /sys%p/value'"

These rules can and should be installed using the following command sequence:

sudo apt install upboard-extras
sudo usermod -a -G gpio ${USER}
sudo usermod -a -G leds ${USER}
sudo usermod -a -G spi ${USER}
sudo usermod -a -G i2c ${USER}
sudo usermod -a -G dialout ${USER}

Activate modules and access
sudo reboot
