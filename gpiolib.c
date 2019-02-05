/*********************************************************************
 * gpiolib.c
 *
 * UPboard GPIO pin manipulation library - uses new port numbering - same as for UP^2
 * board.
 *
 * Author: Willem Scholten
 * Date:   Jan 18 2019
 *
 * This file contains the following core functions:
 *
 * GPIOExport 		- Export the GPIO port for uses
 * GPIOUnexport 	- Unexport GPIO - clean up after ourselves
 * GPIODirection 	- Set the direction (in/out) of GPIO
 * GPIORead				- Read the GPIO
 * GPIOWrite			- Write to the GPIO pin
 *
 * To use as a regular user - none root - a set of UDEV rules must
 * be setup, and the user who is running the program accessing the GPIO
 * must be added to the group GPIO as a user.
 *
 */

 #include <sys/stat.h>
 #include <sys/types.h>
 #include <fcntl.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdbool.h>
 #include <time.h>
 #include <sys/ioctl.h>
 #include <unistd.h>
 #include <stdint.h>
 #include <errno.h>

 #include "gpiolib.h"				// gpio library main header file and function setup
 #include "gpiopin.h"				// PIN library of available pins

// the following function provides a safe way tyo sleep the thread
// it is needed to ensure that the kernel can apply the UDEV rules when
// setting pins up for export
void sleepMillis(uint32_t millis){
  struct timespec sleep;
  sleep.tv_sec = millis / 1000;
  sleep.tv_nsec = (millis % 1000) * 1000000L;
  while(clock_nanosleep(CLOCK_MONOTONIC, 0 , &sleep, &sleep) && errno == EINTR);
}

 int GPIOExport(int pin) {
  // setup the GPIO pins for use - they need to be ecxported first
 	// to make them availabel for use.
 	char buffer[BUFFER_MAX];
 	ssize_t bytes_written;
 	int fd;

 	if (fd != -1) {
 	   close(fd);
 	   fd = open("/sys/class/gpio/export", O_WRONLY);
 		 usleep(1000);
 		 if(fd == -1) {
 			  fprintf(stderr, "Failed to open export for writing for pin: %d!\n", pin);
 			 	return(-1);
 		 }
 		 bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
 		 write(fd, buffer, bytes_written);
 		 close(fd);
 	}
  // check if the binary got root permissions and does the UDEV rules kicked in
  if(geteuid()) {
    fprintf(stderr, "No elevated privileges - sleep the thread\n");
    sleepMillis(100);
  }

 	return(0);
 }

 int GPIOUnexport(int pin){
   // After use of the GPIO pins we need to cleanup after ourselves
 	// by unexporting the GPIO pins
 	char buffer[BUFFER_MAX];
 	ssize_t bytes_written;
 	int fd;
 	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	usleep(1000);
 	if (-1 == fd) {
 		fprintf(stderr, "Failed to open unexport for writing!\n");
 		return(-1);
 	}
 	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
 	write(fd, buffer, bytes_written);
	usleep(1000);		// give process time to finish and relinquish fd

 	close(fd);
 	return(0);
 }

 int GPIODirection(int pin, int dir){
 	// Function to set the direction of the GPIO pin it can be
 	// either in - read or out - write
 	static const char s_directions_str[]  = "in\0out";

 	char path[DIRECTION_MAX];
 	int fd;
   if(DEBUG_ON) {
 		fprintf(stderr, "Pin: %d", pin);
 		fprintf(stderr, " Direction: %d \n", dir);
 	}
 	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
 	fd = open(path, O_WRONLY);
 	usleep(1000);
 	if(DEBUG_ON){
 		fprintf(stderr, "Path: %s \n", path);
 	}
	write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3);
  fsync(fd);            // forse the write to finish
	usleep(1000);         // sleep the trhead to catchup
 	close(fd);
 	return(0);
 }

 int GPIORead(int pin){
 	// Function to read the GPIO pin
 	char path[VALUE_MAX];
 	char value_str[3];
 	int fd;
 	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
 	fd = open(path, O_RDONLY);
 	usleep(1000);				// give process time to finsih and grab fd
 	if (-1 == read(fd, value_str, 3)) {
 		fprintf(stderr, "Failed to read value!\n");
 		return(-1);
 	}
 	close(fd);
 	usleep(1000);				// give process time to finsih and relinguish fd
 	return(atoi(value_str));
 }

 int GPIOWrite(int pin, int value){
   // Function to wreite to the GPIO pin
 	static const char s_values_str[] = "01";
 	char path[VALUE_MAX];
 	int fd;
 	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
 	fd = open(path, O_WRONLY);
  if(DEBUG_ON){
		printf("Write Path:  %s ", path);
    printf(" Value: %d \n", value);
	}
	usleep(500 * 1000);				// give process time to finsih and grab fd
 	if (-1 == fd) {
 		fprintf(stderr, "Failed to open gpio value for writing!\n");
 		return(-1);
 	}
	write(fd, &s_values_str[LOW == value ? 0 : 1], 1);
	fsync(fd);
  usleep(1000);				// give process time to finsih and grab fd

 	close(fd);
 	usleep(1000);
 	return(0);
 }
