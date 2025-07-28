#pragma once
#include "def.h"
#define sfr(str, addr) (*(volatile str *)(addr))

typedef struct {
  u32 CR;
  u32 CFGR;
  u32 CIR;
  u32 APB2RSTR;
  u32 APB1RSTR;
  u32 AHBENR;
  u32 APB2ENR;
  u32 APB1ENR;
  u32 BDCR;
  u32 CSR;
} rcc;
#define RCC sfr(rcc, 0x40021000)

typedef struct {
  u32 ISER[8];
  u32 RE0[24];
  u32 ICER[8];
  u32 RE1[24];
  u32 ISPR[8];
  u32 RE2[24];
  u32 ICPR[8];
  u32 RE3[24];
  u32 IABR[8];
  u32 RE4[56];
  u32 IP[240];
  u32 RE5[644];
  u32 STIR;
} nvic;
#define NVIC sfr(nvic, 0xe000e100)

typedef struct {
  u32 CR1;
  u32 CR2;
  u32 SMCR;
  u32 DIER;
  u32 SR;
  u32 EGR;
  u32 CCMR1;
  u32 CCMR2;
  u32 CCER;
  u32 CNT;
  u32 PSC;
  u32 ARR;
  u32 CCR1;
  u32 CCR2;
  u32 CCR3;
  u32 CCR4;
  u32 DCR;
  u32 DMAR;
} tim;
// #define  TIM2 (*(volatile tim2 *)(0x40000000))
#define TIM2 sfr(tim, 0x40000000)

typedef struct {
  u32 SR;
  u32 DR;
  u32 BRR;
  u32 CR1;
  u32 CR2;
  u32 CR3;
  u32 GTPR;
} usart;
#define USART1 sfr(usart, 0x40013800)

typedef struct{
	u32 CR1;
	u32 CR2;
	u32 OAR1;
	u32 OAR2;
	u32 DR;
	u32 SR1;
	u32 SR2;
	u32 CCR;
	u32 TRISE;
} i2c;
#define I2C1 sfr(i2c,0x40005400)
#define I2C2 sfr(i2c,0x40005800)

typedef struct {
  u32 IMR;
  u32 EMR;
  u32 RTSR;
} exti;
#define EXTI sfr(exti, 0x40010400)

typedef struct {
  u32 CRL;
  u32 CRH;
  u32 IDR;
  u32 ODR;
} gpio;
#define GPIOA sfr(gpio, 0x40010800)
#define GPIOB sfr(gpio, 0x40010c00)
#define GPIOC sfr(gpio, 0x40011000)

typedef struct{
	u32 EVCR;
	u32 MAPR;
	u32 EXITCR1;
	u32 EXITCR2;
	u32 EXITCR3;
	u32 EXITCR4;
}afio;
#define AFIO sfr(afio,0x40010000)

#define FLASH 0x40022000
#define FLASH_ACR (*(volatile u32 *)FLASH)

typedef struct {
  u32 CSR;
  u32 RVR;
  u32 CVR;
  u32 CALIB;
} syst;
#define SYST sfr(syst, 0xe000e010)

typedef struct {
  u32 ISR;
  u32 IFCR;
  u32 CCR1;
  u32 CNDTR1;
  u32 CPAR1;
  volatile u8* CMAR1;
  u32 RE1;
  u32 CCR2;
  u32 CNDTR2;
  u32 CPAR2;
  volatile u8* CMAR2;
  u32 RE2;
  u32 CCR3;
  u32 CNDTR3;
  u32 CPAR3;
  volatile u8* CMAR3;
  u32 RE3;
  u32 CCR4;
  u32 CNDTR4;
  u32 CPAR4;
  volatile u8* CMAR4;
  u32 RE4;
  u32 CCR5;
  u32 CNDTR5;
  u32 CPAR5;
  volatile u8* CMAR5;
  u32 RE5;
  u32 CCR6;
  u32 CNDTR6;
  u32 CPAR6;
  volatile u8* CMAR6;
  u32 RE6;
  u32 CCR7;
  u32 CNDTR7;
  u32 CPAR7;
  volatile u8* CMAR7;
  u32 RE7;
} dma;
#define DMA1 sfr(dma, 0x40020000)
#define DMA2 sfr(dma, 0x40020400)


