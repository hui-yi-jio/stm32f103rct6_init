#include "gpio.h"
void gpio_init() {
  GPIOA.CRL = 0x33333333;
  GPIOA.CRH = 0x333334B3;
  GPIOA.ODR = 0xffffffff;
  GPIOB.CRL = 0xff333333;
  GPIOB.CRH = 0x33333333;
  GPIOC.CRL = 0x33333333;
  GPIOC.CRH = 0x33333333;
  GPIOC.ODR = 0;
}
