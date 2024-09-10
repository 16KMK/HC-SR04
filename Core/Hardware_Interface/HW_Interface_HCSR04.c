#include "HW_Interface_HCSR04.h"
#include "../../Device_Drivers/HC-SR04/HC-SR04.h"

extern TIM_HandleTypeDef htim1;
TIM_IC_InitTypeDef sConfigIC;

uint8_t microseconds_delay = 10;
uint32_t ic_val1 = 0, ic_val2 = 0;  // Input capture values
uint32_t time_diff = 0;
uint8_t first_capture_state = 0;  // Flag to track rising and falling edges
float distance_cm = 0;  // Distance in centimeter

// HC-SR04 hardware interface structure
HCSR04_t hc =
		{ .Hardware_Interface = { .Trigger = hw_trigger, .GetEchoPin =
				hw_read_echo, .counter_start = Timer_Start, .counter_stop =
				Timer_Stop } };

void hw_trigger() {
	// Set TRIG pin high
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET); // Assuming PC14 is TRIG

	// Delay 10 microseconds
	hw_us_delay(10);

	// Set TRIG pin low
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);
}

uint8_t hw_read_echo() {
	return HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN); //ECHO_PIN: 1 for high and 0 for low
}

uint8_t hw_us_delay(uint8_t microseconds_delay) {

	// Reset the timer counter to 0
	htim1.Instance->CNT = 0; //   	__HAL_TIM_SET_COUNTER(&htim1, 0);

	// Start the timer

	uint8_t ok = HAL_TIM_Base_Start(&htim1);

	if (ok != HAL_OK) {
		return 0; //failed to start timer
	}

	// Wait for the required delay
	while (htim1.Instance->CNT < microseconds_delay)
		;

	// stop the timer
	ok = HAL_TIM_Base_Stop(&htim1);
	if (ok != HAL_OK) {
		return 0; //failed to stop timer
	}
	return 1; // success
}

void Timer_Start() {
	HAL_TIM_Base_Start(&htim1);
}

uint16_t Timer_Stop() {
	HAL_TIM_Base_Stop(&htim1);
	return __HAL_TIM_GET_COUNTER(&htim1);
}
