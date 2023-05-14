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

// Comment this line if using an older microcontroller
#define USART_FOR_AVR_1_SERIES

void USART_init( unsigned int baud_rate );
unsigned char USART_rxChar( void );
void USART_txChar( unsigned char c );

void USART_txString( char string[]);
void USART_txUint8( uint8_t num );
void USART_txUint8Bin( uint8_t num );
void USART_txInt16( int16_t num );


#endif /* _USART_LIB_H_ */
