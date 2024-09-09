#include "HC-SR04.h"


hc_sr04_state_t generate_us_delay(uint8_t microseconds_delay) {
	// Use the hardware interface function
	uint8_t counter = 0; //counter of the timer in microseconds
	uint16_t timer;
	uint8_t ok = counter_start(timer);
	if (ok != hc_sr04_success) {
		return 0; //failed to start timer
	}
	while (counter < microseconds_delay)
		;
	ok = counter_stop(timer);
	if (ok != hc_sr04_success) {
		return 0; //failed to stop timer
	}
	return 1; //success
}
;


