# Blinky project for Arm Virtual Hardware

The **Blinky** project can be easily used to verify the basic tool setup.

It is compliant to the [Cortex Microcontroller Software Interface Standard (CMSIS)](https://arm-software.github.io/CMSIS_5/General/html/index.html)
and uses the [CMSIS-RTOS v2 API](https://arm-software.github.io/CMSIS_5/RTOS2/html/index.html) for RTOS functionality. The CMSIS-RTOS v2 API
is supported by various real-time operating systems, for example [Keil RTX5](https://arm-software.github.io/CMSIS_5/RTOS2/html/rtx5_impl.html) or [FreeRTOS](https://github.com/ARM-software/CMSIS-FreeRTOS).

## Operation

 - The application prints alternately "LED On" and "LED Off" to the serial output.

## RTOS: Keil RTX5 Real-Time Operating System

The real-time operating system [Keil RTX5](https://arm-software.github.io/CMSIS_5/RTOS2/html/rtx5_impl.html) implements the resource management. 

It is configured with the following settings:

- [Global Dynamic Memory size](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#systemConfig): 24000 bytes
- [Default Thread Stack size](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#threadConfig): 3072 bytes
- [Event Recorder Configuration](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#evtrecConfig)
  - [Global Initialization](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#evtrecConfigGlobIni): 1
    - Start Recording: 1

Refer to [Configure RTX v5](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html) for a detailed description of all configuration options.

## Board: ARM V2M-MPS3-SSE-300-FVP (AVH)

MPS3 platform for Corstone-300 simulated by [Arm Virtual Hardware (AVH)](https://avh.arm.com).

The heap/stack setup and the CMSIS-Driver assignment is in configuration files of related software components.

### System Configuration

| System Component        | Setting
|:------------------------|:----------------------------------------
| Device                  | SSE-3000-MPS3
| Clock                   | 32 MHz
| Heap                    | 64 kB (configured in region_limit.h file)
| Stack (MSP)             | 1 kB (configured in region_limit.h file)

**STDIO** is routed to USART0

### CMSIS-Driver mapping

| CMSIS-Driver | Peripheral
|:-------------|:----------
| USART0       | USART0
