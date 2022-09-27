/*
 * usart.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Szymon Kajda
 *
 * USART library for regular AVR or 1-series
 * chips (tested only on ATtiny816 so far).
 */

#ifndef _USART_LIB_H_
#define _USART_LIB_H_

#include <avr/io.h>
#include "usart_hardware_1-series/usart_hardware_1-series.h"

extern void USART_init( unsigned int baud_rate );
extern unsigned char USART_rxChar( void );
extern void USART_txChar( unsigned char c );

void USART_txString( char string[]);
void USART_txUint8( uint8_t num );
void USART_txUint8Bin( uint8_t num );


#endif /* _USART_LIB_H_ */
