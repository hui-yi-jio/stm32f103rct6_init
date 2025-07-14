#include "dma.h"
uart_s uart1_rx ;
uart_s uart1_tx ;
void dma1_init(){
	uart1_rx.head = uart1_rx.tail = uart1_tx.head = uart1_tx.tail = 0;
	DMA1.CCR4 = 0x00000090;//  x|1 en
	DMA1.CCR5 = 0x00000080;
	DMA1.CPAR4 = 0x40013804;
	DMA1.CPAR5 = 0x40013804;
	DMA1.CMAR4 = uart1_tx.data;
	DMA1.CMAR5 = uart1_rx.data;
}
