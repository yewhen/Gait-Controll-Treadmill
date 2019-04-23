/*
 * USART.h
 *
 * Created: 2019/4/23 2:55:21
 *  Author: User
 */ 


#ifndef USART_H_
#define USART_H_


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


#endif /* USART_H_ */