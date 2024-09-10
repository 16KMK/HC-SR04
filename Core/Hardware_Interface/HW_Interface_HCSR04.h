#ifndef INC_HW_INTERFACE_HCSR04_H_
#define INC_HW_INTERFACE_HCSR04_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "../../Device_Drivers/HC-SR04/HC-SR04.h"

#define TRIG_PIN GPIO_PIN_1
#define TRIG_PORT GPIOA
#define ECHO_PIN GPIO_PIN_0
#define ECHO_PORT GPIOA

void hw_trigger();

uint8_t hw_read_echo();

uint8_t hw_us_delay(uint8_t microseconds_delay);

void Timer_Start();

uint16_t Timer_Stop();

#endif /* INC_HW_INTERFACE_HCSR04_H_ */
