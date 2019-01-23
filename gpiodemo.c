#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "gpiolib.h"
#include "gpiopin.h"
#include "configgpio.h"

// ---------------------------- test program -------------
int main(int argc, char *argv[])
{
	int repeat = 5;         // for testing of read / write functions

  int gpioIndex = GPIOPIN_ARRAY_LENGTH;

  // Exporting the PINS for use
  do {
    // EXPORT the GPIO gpioPins
    if( -1 == GPIOExport(gpioPins[gpioIndex]))
      return(1);
    if(DEBUG_ON) {
      printf("Setting GPIO: %d \n", gpioPins[gpioIndex]);
    }
  } while(gpioIndex--);

	// Set the direction of the gpioPins
  // Uses two arrays configured in configgpio.h -- make sure that the
  // direction in the gpioPinDirection[] position matches that of the pin you
  // want to set in the gpioPins[] array
  gpioIndex = GPIOPIN_ARRAY_LENGTH;
  do {
    GPIODirection( gpioPins[gpioIndex], gpioPinDirection[gpioIndex]);

    if(DEBUG_ON) {
      printf("Setting GPIO: %d ", gpioPins[gpioIndex]);
      printf("Direction: %d \n", gpioPinDirection[gpioIndex]);
    }
  } while(gpioIndex--);

  // For testing purposes we are going to cylce to the gpioPins array
  // depending on the gpioPinDirection[] for the given pin either read
  // or write to the given pin. We will do so for repeat times.
  gpioIndex = GPIOPIN_ARRAY_LENGTH;
	do {
    gpioIndex = GPIOPIN_ARRAY_LENGTH;
    do {
      if(DEBUG_ON) {
        printf("Pin# %d ", gpioPins[gpioIndex]);
        printf(" Direction: %d \n", gpioPinDirection[gpioIndex]);
      }
      switch(gpioPinDirection[gpioIndex]) {
        case OUT:
          GPIOWrite(gpioPins[gpioIndex], repeat % 2);
        break;

        case IN:
          GPIORead(gpioPins[gpioIndex]);
        break;
      }
    } while(gpioIndex--);
  } while(repeat--);

	// Disable GPIO pins -- pins should be unset but for saftey purposes all
  // pins which were set at output pins should be set to read so there is
  // mo lingering voltage left
  gpioIndex = GPIOPIN_ARRAY_LENGTH;
  do {
     // set direction of pins in OUT state to IN
     if(gpioPinDirection[gpioIndex] == OUT) {
       // set direction to in
       GPIODirection( gpioPins[gpioIndex], IN);
     }
     // Then UNEXPORT the GPIO gpioPins
     if( -1 == GPIOUnexport(gpioPins[gpioIndex]))
        return(1);
     if(DEBUG_ON) {
       printf("UN Setting GPIO: %d \n", gpioPins[gpioIndex]);
     }
  } while(gpioIndex--);

	return(0);
}
