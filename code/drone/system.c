/**
 * system.c
 * Define general constants
 * Initialize peripherals
 */

#include "system.h"

void init_system(void) {
  char data[1];

  LED_init(LED1);
  LED_init(LED2);
  LED_init(LED3);

  // Test connection with RCM
  // LED 2 will blink as long as no connection is established
  while(initConn(USART2) != OK) {
    LED_on(LED2);
    Delay(0x7FFFFF);
    LED_off(LED2);
    Delay(0x7FFFFF);
  }

  // Register with main host
  data[0] = LCM_MSG_REGISTER_NODE;
  if(rcmDataSend(RCM_ANTENNAMODE_TXA_RXA, 1, data))
    LED_on(LED2);

}

void Delay(__IO uint32_t nTick) {
  for(; nTick != 0; nTick--);
}
