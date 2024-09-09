#ifndef INC_HW_INTERFACE_HCSR04_H_
#define INC_HW_INTERFACE_HCSR04_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "../../Device_Drivers/HC-SR04/HC-SR04.h"

uint8_t hc_sr04_hw_us_delay(uint8_t microseconds_delay);
void MX_TIM1_Init(void);
HCSR04_t hc;

#endif /* INC_HW_INTERFACE_HCSR04_H_ */
