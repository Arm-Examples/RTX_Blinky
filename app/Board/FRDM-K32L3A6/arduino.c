/*---------------------------------------------------------------------------
 * Copyright (c) 2021 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *      Name:    arduino.c
 *      Purpose: Arduino module
 *
 *---------------------------------------------------------------------------*/

#include "arduino.h"

#include "pin_mux.h"

#include "fsl_gpio.h"

/**
  \fn          void ARDUINO_IO_D10_Set (uint32_t val)
  \brief       Set IO D10 digital output.
  \param[in]   val output value
                 - 0
                 - 1
  \return      none
*/
void ARDUINO_IO_D10_Set (uint32_t val) {
  GPIO_PinWrite(BOARD_INITARDUINO_SPI_ARDUINO_SPI_SSN_GPIO,
                BOARD_INITARDUINO_SPI_ARDUINO_SPI_SSN_PIN,
                val);
}

/**
  \fn          uint32_t ARDUINO_IO_D9_Get (void)
  \brief       Get IO D9 digital input.
  \return      input state
                 - 0
                 - 1
*/
uint32_t ARDUINO_IO_D9_Get (void) {
  return (GPIO_PinRead(BOARD_INITPINS_ARDUINO_PTB3_ARDUINO_PTB3_GPIO, BOARD_INITPINS_ARDUINO_PTB3_ARDUINO_PTB3_PIN));
}
