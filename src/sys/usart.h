#pragma once
#include "../../include/def.h"
#include "../../include/srf.h"

void usart1_init() ;

void uart1_send(u32 length,volatile u8* data) ;
void uart1_receive(u32 length,volatile u8* data) ;
