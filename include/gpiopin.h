#ifndef _GPIOPIN_H_
#define _GPIOPIN_H

#ifdef __cplusplus
extern "C"
{
#endif

// PIN defintions for the GPIO pin's for the UPboard as of kernel
// 4.15 -- the numbering has changed these numbers may not work for
// subsequent kernel revisions going forward

// FREE GPIO pins - i.e. pins which are not also designated to
// SPI., I2C, TTY, PWM etc
//
// We use for convienance the RPI Chip GPIO number/naming
// which then is mapped to the Linux Kernel numbering
// see: https://wiki.up-community.org/Pinout_UP2#GPIO

#define PLATFORM 1      // 1 -> UPboard


#if(PLATFORM == 1)      // UPboard
  #define BCM4 4        // header pin# 7
  #define BCM27 27      // header pin# 13
  #define BCM22 22      // header pin# 15
  #define BCM5 5        // header pin# 29
  #define BCM6 6        // header pin# 31
  #define BCM26 26      // header pin# 37
  #define BCM23 23      // header pin# 16
  #define BCM24 24      // header pin# 18
  #define BCM25 25      // header pin# 22
  #define BCM16 16      // header pin# 36
#endif

#if(PLATFORM == 2)        // UP^2 Board
  #define BCM4 433        // header pin# 7
  #define BCM27 432       // header pin# 13
  #define BCM22 431       // header pin# 15
  #define BCM5 430        // header pin# 29
  #define BCM6 404        // header pin# 31
  #define BCM26 403       // header pin# 37
  #define BCM23 471       // header pin# 16
  #define BCM24 405       // header pin# 18
  #define BCM25 402       // header pin# 22
  #define BCM16 479       // header pin# 36
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GPIOPIN_H */
