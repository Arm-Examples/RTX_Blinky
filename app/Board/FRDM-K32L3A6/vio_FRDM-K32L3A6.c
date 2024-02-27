/******************************************************************************
 * @file     vio_FRDM-K32L3A6.c
 * @brief    Virtual I/O implementation for board FRDM-K32L3A6
 * @version  V2.0.0
 * @date     23. October 2023
 ******************************************************************************/
/*
 * Copyright (c) 2021-2023 Arm Limited (or its affiliates).
 * All rights reserved.
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
 */

/*! \page vio_FRDM-K32L3A6 Physical I/O Mapping

The table below lists the physical I/O mapping of this CMSIS-Driver VIO implementation.

Virtual Resource  | Variable       | Physical Resource on FRDM-K32L3A6              |
:-----------------|:---------------|:-----------------------------------------------|
vioBUTTON0        | vioSignalIn.0  | PTA0:  User Button (SW2)                       |
vioBUTTON1        | vioSignalIn.1  | PTE8:  User Button (SW3)                       |
vioBUTTON2        | vioSignalIn.2  | PTE9:  User Button (SW4)                       |
vioBUTTON3        | vioSignalIn.3  | PTE12: User Button (SW5)                       |
vioLED0           | vioSignalOut.0 | PTA24: LED RED                                 |
vioLED1           | vioSignalOut.1 | PTA23: LED GREEN                               |
vioLED2           | vioSignalOut.2 | PTA22: LED BLUE                                |
*/

/* History:
 *  Version 2.0.0
 *    Updated to API 1.0.0
 *  Version 1.0.0
 *    Initial release
 */

#include <string.h>
#include "cmsis_vio.h"

#include "RTE_Components.h"                 // Component selection
#include CMSIS_device_header

#if !defined CMSIS_VOUT || !defined CMSIS_VIN
#include "pin_mux.h"
#include "board.h"
#endif

// VIO input, output definitions
#define VIO_VALUE_NUM           3U          // Number of values

// VIO input, output variables
__USED uint32_t vioSignalIn;                // Memory for incoming signal
__USED uint32_t vioSignalOut;               // Memory for outgoing signal
__USED int32_t  vioValue[VIO_VALUE_NUM];    // Memory for value used in vioGetValue/vioSetValue

#if !defined CMSIS_VOUT
// Add global user types, variables, functions here:

#endif

#if !defined CMSIS_VIN
// Add global user types, variables, functions here:

#endif

// Initialize test input, output.
void vioInit (void) {
#if !defined CMSIS_VOUT
// Add user variables here:

#endif
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  vioSignalIn  = 0U;
  vioSignalOut = 0U;

  memset(vioValue, 0, sizeof(vioValue));

#if !defined CMSIS_VOUT
  // Initialize LEDs pins
  BOARD_InitLEDs();
#endif

#if !defined CMSIS_VIN
  // Initialize buttons pins
  BOARD_InitButtons();
#endif
}

// Set signal output.
void vioSetSignal (uint32_t mask, uint32_t signal) {
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  vioSignalOut &= ~mask;
  vioSignalOut |=  mask & signal;

#if !defined CMSIS_VOUT
  // Output signals to LEDs
  if ((mask & vioLED0) != 0U) {
    if ((signal & vioLED0) != 0U) {
      LED1_ON();
    } else {
      LED1_OFF();
    }
  }
  if ((mask & vioLED1) != 0U) {
    if ((signal & vioLED1) != 0U) {
      LED2_ON();
    } else {
      LED2_OFF();
    }
  }
  if ((mask & vioLED2) != 0U) {
    if ((signal & vioLED2) != 0U) {
      LED3_ON();
    } else {
      LED3_OFF();
    }
  }
#endif
}

// Get signal input.
uint32_t vioGetSignal (uint32_t mask) {
  uint32_t signal;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

#if !defined CMSIS_VIN
  // Get input signals from buttons
  // User Button (SW2)
  if ((mask & vioBUTTON0) != 0U) {
    if (GPIO_PinRead(BOARD_INITBUTTONS_SW2_GPIO, BOARD_INITBUTTONS_SW2_PIN) == 0U) {
      vioSignalIn |=  vioBUTTON0;
    } else {
      vioSignalIn &= ~vioBUTTON0;
    }
  }
  // User Button (SW3)
  if ((mask & vioBUTTON1) != 0U) {
    if (GPIO_PinRead(BOARD_INITBUTTONS_SW3_GPIO, BOARD_INITBUTTONS_SW3_PIN) == 0U) {
      vioSignalIn |=  vioBUTTON1;
    } else {
      vioSignalIn &= ~vioBUTTON1;
    }
  }
  // User Button (SW4)
  if ((mask & vioBUTTON2) != 0U) {
    if (GPIO_PinRead(BOARD_INITBUTTONS_SW4_GPIO, BOARD_INITBUTTONS_SW4_PIN) == 0U) {
      vioSignalIn |=  vioBUTTON2;
    } else {
      vioSignalIn &= ~vioBUTTON2;
    }
  }
  // User Button (SW5)
  if ((mask & vioBUTTON3) != 0U) {
    if (GPIO_PinRead(BOARD_INITBUTTONS_SW5_GPIO, BOARD_INITBUTTONS_SW5_PIN) == 0U) {
      vioSignalIn |=  vioBUTTON3;
    } else {
      vioSignalIn &= ~vioBUTTON3;
    }
  }
#endif

  signal = vioSignalIn & mask;

  return signal;
}

// Set value output.
void vioSetValue (uint32_t id, int32_t value) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValue[index] = value;

#if !defined CMSIS_VOUT
// Add user code here:

#endif
}

// Get value input.
int32_t vioGetValue (uint32_t id) {
  uint32_t index = id;
  int32_t  value = 0;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return value;                       /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

//   vioValue[index] = ...;
#endif

  value = vioValue[index];

  return value;
}
