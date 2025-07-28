#include "dma.h"
uart_s uart1_rx;
uart_s uart1_tx;
u8 i2c1_tx[50];
u8 i2c1_rx[14];
void dma1_init() {
  uart1_rx.head = uart1_rx.tail = uart1_tx.head = uart1_tx.tail = 0;
  DMA1.CCR4 = 0x00000090; //  x|1 en
  DMA1.CCR5 = 0x00000080;
  DMA1.CPAR4 = 0x40013804;
  DMA1.CPAR5 = 0x40013804;
  DMA1.CMAR4 = uart1_tx.data;
  DMA1.CMAR5 = uart1_rx.data;

  DMA1.CCR6 = 0x00000090;
  DMA1.CPAR6 = 0x40005404;//(u32)(&I2C1.DR);
  DMA1.CMAR6 = i2c1_tx;
  DMA1.CCR7 = 0x00000080;
  DMA1.CPAR7 = 0x40005404;
  DMA1.CMAR7 = i2c1_rx;
}
