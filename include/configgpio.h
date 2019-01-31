#ifndef _CONFIGGPIO_H_
#define _CONFIGGPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

// For generic testing
//int gpioPins[] = {BCM4, BCM22, BCM23, BCM24};
//int gpioPinDirection[] = {IN, OUT, OUT, IN};

// Pin coonfig for the DimScan System
int gpioPins[] = {BCM22, BCM26, BCM23, BCM24, BCM25, BCM27};
int gpioPinDirection[] = {OUT, OUT, OUT, OUT, OUT, IN};

// Below array index count must match arrays above defining pin's
#define GPIOPIN_ARRAY_LENGTH  5;   // 0 - 4 -- 4 positions

#ifdef __cplusplus
}
#endif

#endif /* _CONFIGGPIO_H */
