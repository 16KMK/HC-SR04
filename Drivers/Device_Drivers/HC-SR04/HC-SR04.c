#include "HC-SR04.h"

#define SOUND_SPEED 343 //speed of sound = 343 m/s

void HC_SR04_ReadDistance(HCSR04_t *sensor, float *Distance) {
	// 1 Trigger
	sensor->Hardware_Interface.Trigger();

	// 2 wait for rising edge
	while (sensor->Hardware_Interface.GetEchoPin() == 0)
		;

	// 3 start timer
	sensor->Hardware_Interface.counter_start();

	// 4 wait for falling edge
	while (sensor->Hardware_Interface.GetEchoPin() == 1)
		;

	// 5 stop timer
	uint16_t Counts = sensor->Hardware_Interface.counter_stop();

	// 6 calculate distance
	*Distance = (float) (Counts * SOUND_SPEED) / (2 * 1000000); //distance in centimeter
}
