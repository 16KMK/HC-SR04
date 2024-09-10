# HC-SR04 Driver for STM32F1

This repository contains a driver for interfacing the HC-SR04 ultrasonic distance sensor with an STM32F1 microcontroller. The driver is designed to work with the STM32 HAL library and utilizes dependency injection for better abstraction and testability.

## Overview

The HC-SR04 is an ultrasonic distance sensor that measures the distance to an object using sound waves. This driver provides an abstraction layer for controlling the sensor and measuring distances.

## Files

- **HC-SR04.c**: Contains the source file of the main driver code for reading distances from the HC-SR04 sensor.
- **HC-SR04.h**: Contains the header file of the main driver code for reading distances from the HC-SR04 sensor.
- **HW_Interface_HCSR04.c**: Contains the source file of the hardware interface implementation including GPIO and Timer operations.
- **HW_Interface_HCSR04.h**: Contains the header file of the hardware interface implementation including GPIO and Timer operations.

## Dependencies

- STM32 HAL Library
- STM32CubeMX for generating initialization code

## Driver Usage

### HC-SR04.c

The `HC-SR04.c` file contains the main functionality for reading distances from the HC-SR04 sensor. The key function provided is:

- **`HC_SR04_ReadDistance(HCSR04_t *sensor, float *Distance)`**: Reads the distance measured by the HC-SR04 sensor and stores it in the `Distance` variable.

### HW_Interface_HCSR04.c

The `HW_Interface_HCSR04.c` file provides the implementation of the hardware-specific functions required by the HC-SR04 driver:

- **`hw_trigger()`**: Sends a pulse to the TRIG pin to start the distance measurement.
- **`hw_read_echo()`**: Reads the status of the ECHO pin to determine if the sensor is receiving the echo signal.
- **`hw_us_delay(uint8_t microseconds_delay)`**: Provides a microsecond delay using a timer.
- **`Timer_Start()`**: Starts the timer.
- **`Timer_Stop()`**: Stops the timer and returns the counter value.

### Hardware Interface Structure

In `HW_Interface_HCSR04.c`, an `HCSR04_t` structure is defined with function pointers for hardware operations. This allows the driver to be decoupled from specific hardware implementations, enabling easier testing and reuse.

```c
HCSR04_t hc = {
    .Hardware_Interface = {
        .Trigger = hw_trigger,
        .GetEchoPin = hw_read_echo,
        .counter_start = Timer_Start,
        .counter_stop = Timer_Stop
    }
};
```

## Example Usage

To use the driver, follow these steps:

1. **Initialize Hardware**: Ensure that the GPIO pins and timer are correctly initialized.

2. **Create HC-SR04 Instance**: Define an `HCSR04_t` instance with the appropriate hardware interface functions.

3. **Read Distance**:

    ```c
    HCSR04_t sensor = hc;
    float distance;
    
    HC_SR04_ReadDistance(&sensor, &distance);
    
    printf("Distance: %.2f cm\n", distance);
    ```

## Integration

### GPIO and Timer Initialization

Make sure to configure the GPIO pins for TRIG and ECHO, and initialize the timer (`htim1` in this case) for use with input capture. The HC-SR04 requires accurate timing, so proper configuration of the timer is essential.

### Timer Configuration

In `HW_Interface_HCSR04.c`, a timer is used to measure the pulse width of the echo signal. Ensure that the timer is configured for input capture mode, and that the interrupt for capture is properly handled.

## Notes

- The HC-SR04 driver assumes that the echo pin is connected to a timer input capture channel.
- The provided timing and delays are based on typical HC-SR04 specifications and may need adjustment based on your specific hardware setup.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- STM32 HAL Library for peripheral abstraction
- STM32CubeMX for initialization code generation

---