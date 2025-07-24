#include "def.h"
#include "srf.h"
#include "sys/dma.h"
#include "sys/gpio.h"
#include "sys/rcc.h"
#include "sys/time.h"
#include "sys/usart.h"

void i2c1_init() {
  I2C1.CCR = 0x801e;
  I2C1.TRISE = 12;
  I2C1.CR2 = 0x0024;
  I2C1.CR1 = 0x0C01;
  I2C1.OAR1 = 0x4002;
  I2C1.OAR2 = 0x0000;
}
void i2c1_send(u32 addr,u32 reg,u32 data){
	I2C1.CR1 |= 1<<8;
	while(!(I2C1.SR1 & 1));
	I2C1.DR = addr;
	while(!(I2C1.SR1 & 1<<1));
	volatile u32 tmp = I2C1.SR1 |= I2C1.SR2;
	while(!(I2C1.SR1 & 1<<7));
	I2C1.DR = reg;
	while(!(I2C1.SR1 & 1<<7));
	I2C1.DR = data;
	I2C1.SR1 |= 1<<9;
}
u8 i2c1_read(){
	while(!(I2C1.SR1 & 1<<6));
	return I2C1.DR;
}
void mpu6050_init(){
	i2c1_send(0x68<<1,0x6B,0);
	i2c1_send(0x68<<1,0x1B,0x18);
	i2c1_send(0x68<<1,0x1C,0x18);
}
void mpu6050_read(i16* accel,i16* gyro,float temp){
	I2C1.CR1 |= 1<<8;
	while(!(I2C1.SR1 & 1));
	I2C1.DR = 0x68<<1;
	while(!(I2C1.SR1 & 1<<1));
	volatile u32 tmp = I2C1.SR1 |= I2C1.SR2;
	while(!(I2C1.SR1 & 1<<7));
	I2C1.DR = 0x3B;
	I2C1.CR1 |= 1<<8;
	while(!(I2C1.SR1 & 1));
	I2C1.DR = (0x68<<1)|1;
	while(!(I2C1.SR1 & 1<<1));
	tmp = I2C1.SR1 |= I2C1.SR2;
	accel[0] = (i2c1_read()<<8) | i2c1_read();
	accel[1] = (i2c1_read()<<8) | i2c1_read();
	accel[2] = (i2c1_read()<<8) | i2c1_read();
	temp = ((i2c1_read()<<8) | i2c1_read())/340.0+36.53;
	gyro[0] = (i2c1_read()<<8) | i2c1_read();
	gyro[1] = (i2c1_read()<<8) | i2c1_read();
	gyro[2] = (i2c1_read()<<8) | i2c1_read();
	I2C1.CR1 |= 1<<9;
}
void reset() {
  rcc_init();
  time2_init();
  usart1_init();
  gpio_init();
  dma1_init();
//  mpu6050_init();
  FLASH_ACR = 0x12;
  while (1) {
    I2C1.CR1 |= 1 << 8;
    if (USART1.SR & 0x00000020) {
      uart1_receive(1, uart1_rx.data);
      uart1_send(1, uart1_rx.data);
     u8 a;
     a = -1;
     uart1_send(1, &a);
    }
	i16 accel[3],gyro[3];
	float temp;
    //mpu6050_read(accel,gyro,temp);
    //uart1_send(6,(u8*)accel);
    GPIOC.ODR = TIM2.CNT;
  }
}

void stack_top();
void time2() { TIM2.SR = 0; }
void usart1() {}

[[gnu::section(".text.ivt"), gnu::used]]
void (*const ivt[])(void) = {stack_top, reset, [44] = time2, [53] = usart1};
