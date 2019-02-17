/*
 * usart_128_02.cpp
 *
 * Created: 1/30/2019 8:52:08 PM
 * Author : user
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	/* Define prescale value */
#include <util/delay.h>

//defining uart//
void USART_Init(unsigned long BAUDRATE);
char USART_RxChar();
void USART_TxChar(char data);



float acc_x, acc_y, acc_z;



int main(void)
{
	USART_Init(4800);
	unsigned char dir;
	DDRG = 0b11000;
	DDRD = 0b11000000;
	DDRB = 0b10010000;
	PORTB |= (1<<PINB4)|(1<<PINB7);
    while (1)
    {
		dir = USART_RxChar();
		// USART_TxChar(dir);
		//_delay_ms(100);
// 		if ((dir != 'F') || (dir != 'B') || (dir != 'R') || (dir != 'L')) {
// 			while(1) {
// 				dir = USART_TxChar();
// 				if ((dir == 'F') || (dir == 'B') || (dir == 'R') || (dir == 'L')) {
// 					break;
// 				}
// 			}
// 		}
		
	//	USART_TxChar(dir);
		switch (dir)
		{
		
		case'F' :
			PORTG |= (1<<PING4);
			PORTG &= ~(1<<PING3);
			PORTD |= (1<<PIND6);
			PORTD &= ~(1<<PIND7);
			break;
			
		case'B' : 
			PORTG &= ~(1<<PING4);
			PORTG |= (1<<PING3);
			PORTD &= ~(1<<PIND6);
			PORTD |= (1<<PIND7);
			break;
		case'R' : 			

			PORTG |= (1<<PING4);
			PORTG &= ~(1<<PING3);
			PORTD &= ~(1<<PIND6);
			PORTD &= ~(1<<PIND7);
		    break;
		case'L':
			PORTG &= ~(1<<PING4);
			PORTG &= ~(1<<PING3);
			PORTD |= (1<<PIND6);
			PORTD &= ~(1<<PIND7);
		    break;
		default:
			PORTG &= ~(1<<PING4);
			PORTG &= ~(1<<PING3);
			PORTD &= ~(1<<PIND6);
			PORTD &= ~(1<<PIND7);
			break;
		/*default:
			PORTG &= ~(1<<PING4);
			PORTG &= ~(1<<PING3);
			PORTD &= ~(1<<PIND6);
			PORTD &= ~(1<<PIND7);
			break;*/
		//PD6 PD7 right motor
		//PG3 PG4 left motor
		}
	}
}

void USART_Init(unsigned long BAUDRATE)				/* USART initialize function */
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);				/* Enable USART transmitter and receiver */
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);	/* Write USCRC for 8 bit data and 1 stop bit */
	UBRR0L = BAUD_PRESCALE;							/* Load UBRRL with lower 8 bit of prescale value */
	UBRR0H = (BAUD_PRESCALE >> 8);					/* Load UBRRH with upper 8 bit of prescale value */
}


char USART_RxChar()									/* Data receiving function */
{
	while (!(UCSR0A & (1 << RXC0)));					/* Wait until new data receive */
	return(UDR0);									/* Get and return received data */
}

void USART_TxChar(char data)						/* Data transmitting function */
{
	UDR0 = data;										/* Write data to be transmitting in UDR */
	while (!(UCSR0A & (1<<UDRE0)));					/* Wait until data transmit and buffer get empty */
}







