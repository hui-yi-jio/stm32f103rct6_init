#include "usart.h"
#include "dma.h"
void usart1_init() {
  USART1.BRR = 0x00000030;
  USART1.CR1 = 0x0000200C;//1500000
  USART1.CR3 = 0x000000C0;
}

void uart1_send(u32 length,volatile u8* data) {
  DMA1.CCR4 &= 0xfffffffe;
  //for(int i = 0;i<length;++i,++uart1_tx.head)uart1_tx.data[uart1_tx.head] = *(data+i);
  for(int i = 0;i<length;++i)uart1_tx.data[i] = *(data+i);
  DMA1.CNDTR4 = length;
  DMA1.CMAR4 = uart1_tx.data;
  //DMA1.CMAR4 = &uart1_tx.data[uart1_tx.tail];
  //uart1_tx.tail += length;
  DMA1.CCR4 |= 1;
}

void uart1_receive(u32 length,volatile u8* data) {
  DMA1.CCR5 &= 0xfffffffe;
  DMA1.CNDTR5 = length;
  DMA1.CMAR5 = data;
  //DMA1.CMAR5 = &uart1_rx.data[uart1_rx.head];
  //uart1_rx.head += length;
  DMA1.CCR5 |= 1;
}
