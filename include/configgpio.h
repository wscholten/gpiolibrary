#ifndef _CONFIGGPIO_H_
#define _CONFIGGPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

// For generic testing
//int gpioPins[] = {BCM4, BCM22, BCM23, BCM24};
//int gpioPinDirection[] = {IN, OUT, OUT, IN};

// Pin config for the DimScan System
int gpioPins[] = {BCM24, BCM25, BCM23, BCM27, BCM5, BCM6, BCM26, BCM22};
int gpioPinDirection[] = {OUT, OUT, OUT, OUT, OUT, OUT, OUT, OUT};

// Below array index count must match arrays above defining pin's
#define GPIOPIN_ARRAY_LENGTH  7;   // 0 - 7 -- 8 positions counting from 0 - max is 7

#ifdef __cplusplus
}
#endif

#endif /* _CONFIGGPIO_H */
