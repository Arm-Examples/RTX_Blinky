/*---------------------------------------------------------------------------
 * Copyright (c) 2020 Arm Limited (or its affiliates). All rights reserved.
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
 *      Name:    Blinky.c
 *      Purpose: RTX example program
 *
 *---------------------------------------------------------------------------*/

#include "main.h"
#include <stdio.h>
#include "cmsis_os2.h"

static osThreadId_t tid_thrLED;         // Thread id of thread: LED

/*---------------------------------------------------------------------------
  thrLED: blink LED
 *---------------------------------------------------------------------------*/
__NO_RETURN static void thrLED (void *arg) {
//  uint32_t active_flag = 0U;

  (void)arg;

  for (;;) {
//    if (osThreadFlagsWait(1U, osFlagsWaitAny, 0U) == 1U) {
//      active_flag ^= 1U;
//    }

//    if (active_flag == 1U) {
////      vioSetSignal(vioLED0, vioLEDoff);         // Switch LED0 off
////      vioSetSignal(vioLED1, vioLEDon);          // Switch LED1 on
//      osDelay(100U);                            // Delay 100 ms
////      vioSetSignal(vioLED0, vioLEDon);          // Switch LED0 on
////      vioSetSignal(vioLED1, vioLEDoff);         // Switch LED1 off
//      osDelay(100U);                            // Delay 100 ms
//    }
//    else {
			printf("LED On\r\n");
      osDelay(500U);                            // Delay 500 ms
			printf("LED Off\r\n");
      osDelay(500U);                            // Delay 500 ms
//    }
  }
}

/*---------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
static void app_main (void *argument) {
  (void)argument;

  tid_thrLED = osThreadNew(thrLED, NULL, NULL);         // Create LED thread
  if (tid_thrLED == NULL) { /* add error handling */ }

  osThreadExit();
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, NULL);
}
