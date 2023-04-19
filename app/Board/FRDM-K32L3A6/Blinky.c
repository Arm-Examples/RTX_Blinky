/*---------------------------------------------------------------------------
 * Copyright (c) 2023 Arm Limited (or its affiliates). All rights reserved.
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
#include "cmsis_vio.h"

// test comment
static   osThreadId_t tid_thrLED;       // Thread id of thread: LED
static   osThreadId_t tid_thrButton;    // Thread id of thread: Button
volatile     uint32_t g_ledSet = 0;     // Variable to store virtual LED value:
                                        // 0 = LED0 off, LED1 off
                                        // 1 = LED0 on,  LED1 off
                                        // 2 = LED0 off, LED1 on
                                        // 3 = LED0 on,  LED1 on

/*---------------------------------------------------------------------------
  thrLED: blink LED
 *---------------------------------------------------------------------------*/
__NO_RETURN static void thrLED (void *arg) {
  uint32_t active_flag = 0U;

  (void)arg;

  for (;;) {
    if (osThreadFlagsWait(1U, osFlagsWaitAny, 0U) == 1U) {
      active_flag ^= 1U;
    }

    if (active_flag == 1U) {
      vioSetSignal(vioLED0, vioLEDoff);         // Switch LED0 off
      vioSetSignal(vioLED1, vioLEDon);          // Switch LED1 on
      g_ledSet = 2;                             // set global variable to '2'
      printf("LED0 Off, LED1 On\r\n");          // Print message
      osDelay(100U);                            // Delay 100 ms
      vioSetSignal(vioLED0, vioLEDon);          // Switch LED0 on
      vioSetSignal(vioLED1, vioLEDoff);         // Switch LED1 off
      g_ledSet = 1;                             // set global variable to '1'
      printf("LED0 On, LED1 Off\r\n");          // Print message
      osDelay(100U);                            // Delay 100 ms
    }
    else {
      vioSetSignal(vioLED0, vioLEDon);          // Switch LED0 on
      g_ledSet = 1;                             // set global variable to '1'
      printf("LED0 On\r\n");                    // Print message
      osDelay(500U);                            // Delay 500 ms
      vioSetSignal(vioLED0, vioLEDoff);         // Switch LED0 off
      g_ledSet = 0;                             // set global variable to '0'
      printf("LED0 Off\r\n");                   // Print message
      osDelay(500U);                            // Delay 500 ms
    }
  }
}

/*---------------------------------------------------------------------------
  thrButton: check Button state
 *---------------------------------------------------------------------------*/
__NO_RETURN static void thrButton (void *arg) {
  uint32_t last = 0U;
  uint32_t state;

  (void)arg;

  for (;;) {
    state = (vioGetSignal(vioBUTTON0));           // Get pressed Button state
    if (state != last) {
      if (state == 1U) {
        osThreadFlagsSet(tid_thrLED, 1U);         // Set flag for thrLED
      }
      last = state;
    }
    osDelay(100U);
  }
}

/*---------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
static void app_main (void *argument) {
  (void)argument;

  tid_thrLED = osThreadNew(thrLED, NULL, NULL);         // Create LED thread
  if (tid_thrLED == NULL) { /* add error handling */ }

  tid_thrButton = osThreadNew(thrButton, NULL, NULL);   // Create Button thread
  if (tid_thrButton == NULL) { /* add error handling */ }

  osThreadExit();
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, NULL);
}
