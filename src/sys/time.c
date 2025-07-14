#include "time.h"
void time2_init() {
  NVIC.ISER[0] = 1 << 28;
  TIM2.CR1 = 0x00000001;
  TIM2.DIER = 1;
  TIM2.PSC = 35955; // 1ms
  TIM2.ARR = 999;   // 10ms
}
