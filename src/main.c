#include "def.h"
#include "srf.h"
#include "sys/dma.h"
#include "sys/gpio.h"
#include "sys/rcc.h"
#include "sys/time.h"
#include "sys/usart.h"

void i2c1_init() {
  I2C1.CR1 = 0x8000;
  I2C1.CCR = 0x801e;
  I2C1.TRISE = 12;
  I2C1.CR2 = 0x0f24;
  I2C1.CR1 = 0x0401;
  I2C1.OAR1 = 0x4002;
  I2C1.OAR2 = 0x0000;
  // I2C1.CR2 = 0x0024;
  // I2C1.OAR1 = 0x4002;
  // I2C1.OAR2 = 0;
  // I2C1.CCR = 0x00b4;
  // I2C1.TRISE = 37;
  // I2C1.CR1 = 0x0001;
}
void i2c1_send(u32 addr, u32 reg, u8 data) {
  I2C1.CR1 |= 1 << 8;
  //	while(!(I2C1.SR1 & 1));
  I2C1.DR = addr;
  //	while(!(I2C1.SR1 & 1<<1));
  volatile u32 tmp = I2C1.SR1 |= I2C1.SR2;
  //	while(!(I2C1.SR1 & 1<<7));
  I2C1.DR = reg;
  //	while(!(I2C1.SR1 & 1<<7));
  I2C1.DR = data;
  I2C1.SR1 |= 1 << 9;
}
u8 i2c1_read() {
  while (!(I2C1.SR1 & 1 << 6))
    ;
  return I2C1.DR;
}
void mpu6050_init() {
  i2c1_send(0x68 << 1, 0x6B, 0);
  //	i2c1_send(0x68<<1,0x1B,0x18);
  //	i2c1_send(0x68<<1,0x1C,0x18);
}
void mpu6050_read(i16 *accel, i16 *gyro, float temp) {
  I2C1.CR1 |= 1 << 8;
  while (!(I2C1.SR1 & 1))
    ;
  I2C1.DR = 0x68 << 1;
  while (!(I2C1.SR1 & 1 << 1))
    ;
  volatile u32 tmp = I2C1.SR1 |= I2C1.SR2;
  while (!(I2C1.SR1 & 1 << 7))
    ;
  I2C1.DR = 0x3B;
  I2C1.CR1 |= 1 << 8;
  while (!(I2C1.SR1 & 1))
    ;
  I2C1.DR = (0x68 << 1) | 1;
  while (!(I2C1.SR1 & 1 << 1))
    ;
  tmp = I2C1.SR1 |= I2C1.SR2;
  accel[0] = (i2c1_read() << 8) | i2c1_read();
  accel[1] = (i2c1_read() << 8) | i2c1_read();
  accel[2] = (i2c1_read() << 8) | i2c1_read();
  temp = ((i2c1_read() << 8) | i2c1_read()) / 340.0 + 36.53;
  gyro[0] = (i2c1_read() << 8) | i2c1_read();
  gyro[1] = (i2c1_read() << 8) | i2c1_read();
  gyro[2] = (i2c1_read() << 8) | i2c1_read();
  I2C1.CR1 |= 1 << 9;
}
void reset() {
  rcc_init();
  time2_init();
  usart1_init();
  gpio_init();
  dma1_init();
  i2c1_init();
  FLASH_ACR = 0x12;
  //mpu6050_init();
    I2C1.CR1 |= 1 << 8;
  while (1) {
    if (USART1.SR & 0x00000020) {
      uart1_receive(1, uart1_rx.data);
      uart1_send(1, uart1_rx.data);
    }
    //	i16 accel[3],gyro[3];
    //	float temp;
    // mpu6050_read(accel,gyro,temp);
    // uart1_send(6,(u8*)accel);
    GPIOC.ODR = TIM2.CNT;
  }
}

void stack_top();
void time2() { TIM2.SR = 0; }
void i2c1_ev() {
  if (I2C1.SR1 & 1) {     // SB
    I2C1.DR = i2c1_tx[0]; // addr;
	uart1_send(2,(u8*)"SB");
  } else if (I2C1.SR1 & 2) { // ADDR
    volatile u32 tmp = I2C1.SR1 |= I2C1.SR2;
    I2C1.DR = i2c1_tx[1];//reg;
  } else if (I2C1.SR1 & 1 << 6) { // RxNE

  } else if (I2C1.SR1 & 1 << 7) { // TxE
    I2C1.DR = i2c1_tx[2];//data;
    I2C1.SR1 |= 1 << 9;

  } else if (I2C1.SR1 & 4) { // BTF

  } else if (I2C1.SR1 & 1 << 4) { // STIOPF
  }
}
void i2c1_er() {
  if (I2C1.SR1 & 1 << 8) { // BERR
    uart1_send(4, (u8 *)("BERR"));
  } else if (I2C1.SR1 & 1 << 9) { // ARLO
    uart1_send(4, (u8 *)("ARLO"));
  } else if (I2C1.SR1 & 1 << 10) { // AF
    uart1_send(4, (u8 *)("AF"));
  } else if (I2C1.SR1 & 1 << 11) { // OVR
    uart1_send(4, (u8 *)("OVR"));
  } else if (I2C1.SR1 & 1 << 12) { // PECERR
    uart1_send(4, (u8 *)("PECERR"));
  } else if (I2C1.SR1 & 1 << 14) { // TIMEOUT
    uart1_send(4, (u8 *)("TIMEOUT"));
  }
}
void usart1() {}

[[gnu::section(".text.ivt"), gnu::used]]
void (*const ivt[])(void) = {
    stack_top, reset, [44] = time2, [47] = i2c1_ev, i2c1_er, [53] = usart1};
