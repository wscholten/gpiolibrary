#ifndef _GPIO_H_
#define _GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif
// General include file for the GPIO routines

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define BUFFER_MAX 4			// 3 digit pin + NULL
#define DIRECTION_MAX 36	// pin 3digit +  NULL
#define VALUE_MAX 31			// pin 3digit + NULL

#define DEBUG_ON true
#define DEBUG_LIB_ON false    // library code debug ccoode on/off

// EXPORT pin function
int GPIOExport(int pin);

// UNexport pin function
int GPIOUnexport(int pin);

// Set the direction of the pin
int GPIODirection(int pin, int dir);

// Read the value of the pin
int GPIORead(int pin);

// Write to the GPIO pin
int GPIOWrite(int pin, int value);

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H */
