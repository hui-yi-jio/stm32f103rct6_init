#include "def.h"
#include "srf.h"
#include "sys/dma.h"
#include "sys/gpio.h"
#include "sys/rcc.h"
#include "sys/time.h"
#include "sys/usart.h"

void reset() {
  rcc_init();
  time2_init();
  usart1_init();
  gpio_init();
  dma1_init();
  FLASH_ACR = 0x12;
  while (1) {
	if(USART1.SR & 0x00000020) {
	 uart1_receive(2);
	 uart1_send(2,uart1_rx.data);
	 //uart1_send(1,&uart1_rx.data[uart1_rx.tail]);
	 uart1_rx.tail += 1;
	}
    GPIOC.ODR = TIM2.CNT;
  }
}

void stack_top();
void time2() {
  TIM2.SR = 0;
}
void usart1() {}

[[gnu::section(".text.ivt"), gnu::used]]
void (*const ivt[])(void) = {stack_top, reset, [44] = time2, [53] = usart1};
