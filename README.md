# Blinky Project for Multiple Targets
[![CMSIS Compliance](https://img.shields.io/github/actions/workflow/status/Arm-Examples/RTX_Blinky/verify.yml?logo=arm&logoColor=0091bd&label=CMSIS%20Compliance)](https://www.keil.arm.com/cmsis) 

<p align="center"><img src="./Blinky.png"/></p>

The **Blinky** project can be easily used to verify the basic tool setup. It is available for two different targets:

- Arm Cortstone-300 (Cortex-M55)
- NXP K32L3A60VPJ1A (dual-core Cortex-M0+/Cortex-M4)

It is compliant to the [Cortex Microcontroller Software Interface Standard (CMSIS)](https://arm-software.github.io/CMSIS_6/latest/General/index.html)
and uses the [CMSIS-RTOS v2 API](https://arm-software.github.io/CMSIS_6/latest/RTOS2/index.html) for RTOS functionality. The CMSIS-RTOS v2 API
is supported by various real-time operating systems, for example [Keil RTX5](https://arm-software.github.io/CMSIS-RTX/latest/index.htmll) or [FreeRTOS](https://github.com/ARM-software/CMSIS-FreeRTOS).

## Operation

### Flashing the FRDM-K32L3A6 taarget

You have two options to flash the hardware target with Keil Studio:

1. Use the embedded debugger: when pressing the Run or Debug button, the embedded debugger is called to flash the application onto the target.
1. Use the Arm Debugger: in the `tasks.json` file, there is an entry for the new Arm Debugger. If you want to flash the target with this debugger, go to "Terminal --> Run Task..." and select "Flash K32 with Arm Debugger".

In both cases, use the "cm4" target in the selection pop-up:

![Select processor](./select_processor.png)

### Debugging on the FRDM-K32L3A6 taarget

You have two options to debug the hardware target with Keil Studio:

1. Use the embedded debugger: when pressing the Debug button, the embedded debugger is called to debug the application onto the target.
1. Use the Arm Debugger: in the `launch.json` file, there is an entry for the new Arm Debugger. If you want to debug the target with this debugger, go to the debug view (1), select the launch configuration in the drop-down at the top ("Arm Debug")(2), and press the debug button(3):
   
   ![Use Arm Debug](./Arm_Debug.png)

In both cases, use the "cm4" target in the selection pop-up:

![Select processor](./select_processor.png)

### Running the application

- In the beginning, `vioLED0` blinks in 1 sec interval.
- Pressing `vioBUTTON0` changes the blink frequency and start/stops `vioLED1`.
- `printf` messages are shown on the serial console.

The board hardware mapping of `vioLED0`, `vioLED1`, and `vioBUTTON0` depends on the 
configuration of the [CMSIS-Driver VIO](https://arm-software.github.io/CMSIS_6/latest/Driver/group__vio__interface__gr.html).

The output of the serial console can be observed in a Terminal window on VS Code.

## RTOS: Keil RTX5 Real-Time Operating System

The real-time operating system [Keil RTX5](https://arm-software.github.io/CMSIS-RTX/latest/index.html) implements the resource management. 

It is configured with the following settings:

- [Global Dynamic Memory size](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#systemConfig): 24000 bytes
- [Default Thread Stack size](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#threadConfig): 3072 bytes
- [Event Recorder Configuration](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#evtrecConfig)
  - [Global Initialization](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#evtrecConfigGlobIni): 1
    - Start Recording: 1

Refer to [Configure RTX v5](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#evtrecConfigGlobInil) for a detailed description of all configuration options.

## Board: ARM V2M-MPS3-SSE-300-FVP (AVH)

MPS3 platform for Corstone-300 simulated by [Arm Virtual Hardware (AVH)](https://avh.arm.com).

The heap/stack setup and the CMSIS-Driver assignment is in configuration files of related software components.

### System Configuration

| System Component        | Setting
|:------------------------|:----------------------------------------
| Device                  | SSE-3000-MPS3
| Clock                   | 32 MHz
| Heap                    | 64 kB (configured in region_limit.h file)
| Stack (MSP)             |  1 kB (configured in region_limit.h file)

**STDIO** is routed to USART0

### CMSIS-Driver mapping

| CMSIS-Driver | Peripheral
|:-------------|:----------
| USART0       | USART0

| CMSIS-Driver VIO  | Physical Resource on V2M-MPS3-SSE-300
|:------------------|:-------------------------------------
| vioBUTTON0        | User Button PB0
| vioLED0           | User LED UL0
| vioLED1           | User LED UL1

*Note:* On AVH, the LEDs and the button are simulated in a graphical window.

## Board: NXP FRDM-K32L3A6

The tables below list the device configuration for this board. The board layer for the NXP FRDM-K32L3A6 is using the software component `::Board Support: SDK Project Template: project_template (Variant: frdmk32l3a6)` from `NXP.FRDM-K32L3A6_BSP.17.0.0` pack.

The heap/stack setup and the CMSIS-Driver assignment is in configuration files of related software components.

The example project can be re-configured to work on custom hardware. Refer to ["Configuring Example Projects with MCUXpresso Config Tools"](https://github.com/MDK-Packs/Documentation/tree/master/Using_MCUXpresso) for information.

### System Configuration

| System Component        | Setting
|:------------------------|:-------------------------------------------------------------
| Device                  | K32L3A60VPJ1A:cm4
| Board                   | FRDM-K32L3A6
| SDK Version             | ksdk2_0
| Heap                    | 64 kB (configured in linker script K32L3A60xxx_cm4*.scf file)
| Stack (MSP)             |  1 kB (configured in linker script K32L3A60xxx_cm4*.scf file)

### Clock Configuration

| Clock                   | Setting
|:------------------------|:-------
| FIRC                    |  48 MHz
| FIRC DIV1 clock         |  48 MHz
| FIRC DIV2 clock         |  48 MHz
| FIRC DIV3 clock         |  48 MHz
| LPUART0 clock           |  48 MHz
| LPUART1 clock           |  48 MHz
| LPSPI0 clock            |  48 MHz
| LPI2C3 clock            |  48 MHz

**Note:** configured with Functional Group: `BOARD_BootClockRUN`

### GPIO Configuration and usage

| Functional Group            | Pin | Peripheral | Signal   | Identifier         | Pin Settings                           | Usage
|:----------------------------|:----|:-----------|:---------|:-------------------|:---------------------------------------|:-----------------------------------
| BOARD_InitDEBUG_UART        | N2  | LPUART0    | TX       | DEBUG_UART0_TX     | default                                | LPUART0 TX for debug console (PTC8)
| BOARD_InitDEBUG_UART        | P3  | LPUART0    | RX       | DEBUG_UART0_RX     | default                                | LPUART0 RX for debug console (PTC7)
| BOARD_InitLEDs              | D6  | GPIOA      | GPIO, 24 | RGB_RED            | default                                | User LED1 (PTA24)
| BOARD_InitLEDs              | E6  | GPIOA      | GPIO, 23 | RGB_GREEN          | default                                | User LED2 (PTA23)
| BOARD_InitLEDs              | B6  | GPIOA      | GPIO, 22 | RGB_BLUE           | default                                | User LED3 (PTA22)
| BOARD_InitButtons           | B10 | GPIOA      | GPIO,  0 | SW2                | default                                | User Button SW2 (PTA2)
| BOARD_InitButtons           | P16 | GPIOE      | GPIO,  8 | SW3                | default                                | User Button SW3 (PTE8)
| BOARD_InitButtons           | N16 | GPIOE      | GPIO,  9 | SW4                | default                                | User Button SW4 (PTE9)
| BOARD_InitButtons           | L12 | GPIOE      | GPIO, 12 | SW5                | default                                | User Button SW5 (PTE12)
| BOARD_InitARDUINO_UART      | A5  | LPUART1    | TX       | ARDUINO_LPUART1_TX | default                                | Arduino UNO R3 pin D1 (PTA26)
| BOARD_InitARDUINO_UART      | B5  | LPUART1    | RX       | ARDUINO_LPUART1_RX | default                                | Arduino UNO R3 pin D0 (PTA27)
| BOARD_InitARDUINO_SPI       | C2  | LPSPI0     | SCK      | ARDUINO_SPI_SCK    | default                                | Arduino UNO R3 pin D13 (PTB4)
| BOARD_InitARDUINO_SPI       | D2  | LPSPI0     | SOUT     | ARDUINO_SPI_MOSI   | default                                | Arduino UNO R3 pin D11 (PTB5)
| BOARD_InitARDUINO_SPI       | E2  | LPSPI0     | SIN      | ARDUINO_SPI_MISO   | default                                | Arduino UNO R3 pin D12 (PTB7)
| BOARD_InitARDUINO_SPI       | E1  | GPIOB      | GPIO,  6 | ARDUINO_SPI_SSN    | Direction Output, GPIO initial state 1 | Arduino UNO R3 pin D10 (PTB6)
| BOARD_InitPins_Arduino_PTB3 | C1  | GPIOB      | GPIO,  3 | ARDUINO_PTB3       | Direction Input                        | Arduino UNO R3 pin D9  (PTB3)

### NVIC Configuration

| NVIC Interrupt      | Priority
|:--------------------|:--------
| LPUART1             | 4
| LPSPI0              | 4

**STDIO** is routed to a debug console through Virtual COM port (DAP-Link, peripheral = LPUART0, baudrate = 115200)

### CMSIS-Driver mapping

| CMSIS-Driver | Peripheral
|:-------------|:----------
| USART1       | LPUART1

| CMSIS-Driver VIO  | Physical board hardware
|:------------------|:------------------------------
| vioBUTTON0        | User Button SW2
| vioLED0           | User LED RED
| vioLED1           | User LED GREEN
