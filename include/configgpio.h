#ifndef _CONFIGGPIO_H_
#define _CONFIGGPIO_H

#ifdef __cplusplus
extern "C"
{
#endif


int gpioPins[] = {BCM4, BCM22, BCM23, BCM24};
int gpioPinDirection[] = {IN, OUT, OUT, IN};

#define GPIOPIN_ARRAY_LENGTH  3;   // 0 - 4 -- 4 positions

#ifdef __cplusplus
}
#endif

#endif /* _CONFIGGPIO_H */
