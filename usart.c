/*
 * usart.c
 *
 *  Created on: Sep 27, 2022
 *      Author: Szymon Kajda
 */

#include "usart.h"

#include <avr/io.h>

void USART_txString( char string[]){
	int i=0;
	while(string[i] != 0x00){
		USART_txChar(string[i]);
		i++;
	}
}

void USART_txUint8( uint8_t num ){
	uint8_t rem, len = 3;	// 3 digits to print
	char buf[len+1];

	for( uint8_t i=0; i<8; i++ ){
		rem = num % 10;
		num = num / 10;
		buf[len - (i + 1)] = rem + '0';
	}

	buf[len] = '\0';

	USART_txString( buf );
}

void USART_txUint8Bin( uint8_t num ){
	uint8_t rem, len = 8;	// 8 bits to print
	char buf[len+1];

	for( uint8_t i=0; i<8; i++ ){
		rem = num % 2;
		num = num / 2;
		buf[len - (i + 1)] = rem + '0';
	}

	buf[len] = '\0';

	USART_txString( buf );
}
