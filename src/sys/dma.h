#pragma once
#include "../../include/def.h"
#include "../../include/srf.h"
typedef struct{
	volatile u8 data[256];
	u8 head;
	u8 tail;
}uart_s;
extern uart_s uart1_rx;
extern uart_s uart1_tx;
extern u8 i2c1_tx[50];
extern u8 i2c1_rx[14];
void dma1_init();
