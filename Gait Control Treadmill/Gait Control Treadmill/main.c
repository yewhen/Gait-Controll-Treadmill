/*
 * Gait Control Treadmill.c
 *
 * Created: 2019/4/23 0:49:17
 * Author : User
 */ 

#include "PWM.h"
#include "Interrupt.h"
#include <stdio.h>

#define BAUD				9600
#define MYUBBR				F_CPU/16/BAUD-1



void USART_Init(unsigned int ubrr){
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (3<<UCSZ00);
}
unsigned char USART_Receive(){
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}
void USART_Transmit(unsigned char data){
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
void USART_putstring(char* strptr){
	while (*strptr != 0x00){
		USART_Transmit(*strptr);
		strptr++;
	}
}


int main(){
	Sensor_Init();
	USART_Init(MYUBBR);
	
	char s2[] = "hello";

    //PWM_Init_8();
	sei();
	int prev = 0, cur = 0;
    while (1){
		char s[5];
		
		//int idx;
		// Trig Signal
		PORTB |= (1<<PINB3); 
		_delay_us(15); 
		PORTB &= ~(1<<PINB3);
		
		cur = sensors[0].pulse / 58;
		//if (cur != 0) LED_ON;
		sprintf(s, "%d", cur);
		USART_putstring(s);
		_delay_ms(1000);
		/*for (idx = 0; idx < NUM_SENSOR; idx++){
		
		
		}*/
		//cur = sensors[0].pulse/58;
	}
	return 0;
}


