#ifndef CMSIS_DELAY_MICROS_DWT_STM32_DELAY_H_
#define CMSIS_DELAY_MICROS_DWT_STM32_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
uint32_t DWT_Delay_Init(void);

/**
 * @brief  This function provides a delay (in microseconds)
 * @param  microseconds: delay in microseconds
 */
__STATIC_INLINE void DWT_Delay_us (volatile uint32_t microseconds_delay) {
	uint32_t clk_cycle_start = DWT->CYCCNT;

	/* Go to number of cycles for system */
	microseconds_delay *= (HAL_RCC_GetHCLKFreq() / 1000000);

	/* Delay till end */
	while ((DWT->CYCCNT - clk_cycle_start) < microseconds_delay)
		;
}

#ifdef __cplusplus
}
#endif

#endif /* CMSIS_DELAY_MICROS_DWT_STM32_DELAY_H_ */
