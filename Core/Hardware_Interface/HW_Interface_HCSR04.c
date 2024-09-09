#include "HW_Interface_HCSR04.h"
#include "../../Device_Drivers/HC-SR04/HC-SR04.h"

TIM_HandleTypeDef htim1;
TIM_IC_InitTypeDef sConfigIC;

#define TRIG_PIN GPIO_PIN_14
#define TRIG_PORT GPIOC
#define ECHO_PIN GPIO_PIN_15
#define ECHO_PORT GPIOC
#define SOUND_SPEED 0.0343f //speed of sound = 0.0343 cm/us

uint8_t microseconds_delay = 10;
uint32_t ic_val1 = 0, ic_val2 = 0;  // Input capture values
uint32_t time_diff = 0;
uint8_t first_capture_state = 0;  // Flag to track rising and falling edges
float distance_cm = 0;  // Distance in cm

uint8_t hc_sr04_hw_us_delay(uint8_t microseconds_delay) {

	// Reset the timer counter to 0
	htim1.Instance->CNT = 0; //    __HAL_TIM_SET_COUNTER(&htim1, 0);

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
;

// HC-SR04 hardware interface structure
HCSR04_t hc = { .Hardware_Interface = {
		.generate_us_delay = hc_sr04_hw_us_delay,
		.counter_start =HAL_TIM_Base_Start,
		.counter_stop = HAL_TIM_Base_Stop } };

void hc_sr04_trigger() {
	// Set TRIG pin high
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET); // Assuming PC14 is TRIG

	// Delay 10 microseconds
	hc_sr04_hw_us_delay(10);

	// Set TRIG pin low
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);
}

// Input capture interrupt callback (called when an edge is detected)
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {  // TIM1 CH1
		if (first_capture_state == 0) {
			// First rising edge (ECHO goes high)
			ic_val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // Read first value
			first_capture_state = 1;

			// Switch to capture falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		} else if (first_capture_state == 1) {
			// Falling edge (ECHO goes low)
			ic_val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // Read second value

			if (ic_val2 > ic_val1) {
				time_diff = ic_val2 - ic_val1;
			} else {
				time_diff = (0xFFFF - ic_val1) + ic_val2;
			}

			distance_cm = (time_diff * 0.0343f) / 2.0f;

			// Reset for the next capture
			first_capture_state = 0;

			// Switch back to capture rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_RISING);
		}
	}
}
