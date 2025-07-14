#include "rcc.h"
void rcc_init() {
  RCC.CFGR = 0x061D8400;
  RCC.CR = 0x01010001;
  RCC.CFGR = 0x061D8402;
  RCC.AHBENR = 0xffffffff;
  RCC.APB2ENR = 0xffffffff;
  RCC.APB1ENR = 0xffffffff;
}
