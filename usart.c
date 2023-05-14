/*
 * usart.c
 *
 *  Created on: Sep 27, 2022
 *      Author: Szymon Kajda
 */

#include <avr/io.h>
#include "usart.h"

#ifdef USART_FOR_AVR_1_SERIES

#ifndef F_CPU
#warning "You haven't defined F_CPU. I'm using F_CPU = 3333333"
#define F_CPU 3333333
#endif

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void USART_init( unsigned int baud_rate ){
	PORTB.OUTSET = PIN2_bm;
	PORTB.DIRSET = PIN2_bm;
	PORTB.DIRCLR = PIN3_bm;
	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(baud_rate);
	USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}

unsigned char USART_rxChar( void ){
	while(!(USART0.STATUS & USART_RXCIF_bm));
	return USART0_RXDATAL;
}

void USART_txChar( unsigned char c ){
	while(!(USART0.STATUS & USART_DREIF_bm));
	USART0.TXDATAL = c;
}

#else

#ifndef F_CPU
#warning "You haven't defined F_CPU. I'm using F_CPU = 1000000"
#define F_CPU 1000000
#endif

#define UBRRVAL(BAUD_RATE) F_CPU/16/BAUD_RATE-1

void USART_init( unsigned int baud_rate ){
	UBRR0H = (unsigned char)(UBRRVAL(baud_rate)>>8);
	UBRR0L = (unsigned char)UBRRVAL(baud_rate);
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
}

unsigned char USART_rxChar( void ){
	//while(bit_is_clear(UCSR0A,RXC0));
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void USART_txChar( unsigned char c ){
	//while(bit_is_clear(UCSR0A,UDRE0));
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
}

#endif

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

	if( num == 0 ){
		for( uint8_t i=0; i < len; i++ )
			buf[i] = '0';
	}

	uint8_t i=0;
	while( num ){
		rem = num % 10;
		num = num / 10;
		buf[len - (i + 1)] = rem + '0';
		i++;
	}

	buf[len] = '\0';

	USART_txString( buf );
}

void USART_txUint8Bin( uint8_t num ){
	uint8_t rem, len = 8;	// 8 bits to print
	char buf[len+1];

	if( num == 0 ){
		for( uint8_t i=0; i < len; i++ )
			buf[i] = '0';
	}

	uint8_t i=0;
	while( num ){
		rem = num % 2;
		num = num / 2;
		buf[len - (i + 1)] = rem + '0';
		i++;
	}

	buf[len] = '\0';

	USART_txString( buf );
}

void USART_txUint8Hex( uint8_t num ){
	uint8_t rem, len = 3;	// 3 digits to print (+'h')
	char buf[len+1];

	if( num == 0 ){
		for( uint8_t i=0; i < len-1; i++ )
			buf[i] = '0';
	}

//	W I P
//	uint8_t i=0;
//	while( num ){
//		rem = num % 2;
//		num = num / 2;
//		buf[len - (i + 1)] = rem + '0';
//		i++;
//	}



	buf[len-1] = 'h';
	buf[len] = '\0';

	USART_txString( buf );
}

void USART_txInt16( int16_t num ){
	uint8_t rem, len = 6;	// 6 digits to print (including '-')
	char buf[len+1];

//	if( num == 0 ){
		for( uint8_t i=0; i < len; i++ )
			buf[i] = '0';
//	}
	if( num < 0 ){
		buf[0] = '-';
		num = -num;
	}
	else
		buf[0] = ' ';

	uint8_t i=0;
	while( num ){
		rem = num % 10;
		num = num / 10;
		buf[len - (i + 1)] = rem + '0';
		i++;
	}

	buf[len] = '\0';

	USART_txString( buf );
}
