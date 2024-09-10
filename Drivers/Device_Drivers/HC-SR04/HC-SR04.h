#ifndef DEVICE_DRIVERS_HC_SR04_HC_SR04_H_
#define DEVICE_DRIVERS_HC_SR04_HC_SR04_H_

#include <stdint.h>

// Structure for hardware interface functions
typedef struct {
	struct {
		/// @fn uint8_t (*)()
		/// @brief
		/// Sets the trig pin to logic 1, waits for 10us then sets it to logic 0
		void (*Trigger)();

		/// @fn uint8_t (*)()
		/// @brief
		/// Reads the logic level of the Echo pin, 1 for high and 0 for low
		/// @return
		uint8_t (*GetEchoPin)();

		/// @fn uint8_t (*)()
		/// @brief
		/// Clears the counter and then Starts the timer
		/// @return
		void (*counter_start)();

		/// @fn uint16_t (*)()
		/// @brief
		/// Stops the timer and returns the elapsed counts where 1 count = 1us
		/// @return
		uint16_t (*counter_stop)();

	} Hardware_Interface;
} HCSR04_t;

// enum for return state
typedef enum {
	hc_sr04_failed = 0, hc_sr04_success = 1,
} hc_sr04_state_t;

// Function to generate delay using hardware interface
hc_sr04_state_t generate_us_delay(uint8_t microseconds_delay);
void HC_SR04_ReadDistance(HCSR04_t *sensor, float *Distance) ;
#endif /* DEVICE_DRIVERS_HC_SR04_HC_SR04_H_ */
