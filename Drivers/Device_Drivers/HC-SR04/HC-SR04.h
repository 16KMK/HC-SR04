#ifndef DEVICE_DRIVERS_HC_SR04_HC_SR04_H_
#define DEVICE_DRIVERS_HC_SR04_HC_SR04_H_

#include <stdint.h>

// Structure for hardware interface functions
typedef struct {
	struct {
		uint8_t (*generate_us_delay)(uint8_t microseconds_delay);
		uint8_t (*counter_start);
		uint8_t (*counter_stop);
	} Hardware_Interface;
} HCSR04_t;

// enum for return state
typedef enum {
	hc_sr04_failed = 0, hc_sr04_success = 1,
} hc_sr04_state_t;

// Function to generate delay using hardware interface
hc_sr04_state_t generate_us_delay(uint8_t microseconds_delay);

#endif /* DEVICE_DRIVERS_HC_SR04_HC_SR04_H_ */
