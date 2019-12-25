/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: EmbeddedFab
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "MCAL/UART.h"
#include <avr/interrupt.h>
#include "uart.h"

#include "stdlib.h"
#include "string.h"


#define TRUE 1
#define FALSE 0
#define DEFAULT_BUFFER_SIZE 100
char Rec_Data[DEFAULT_BUFFER_SIZE];
char Counter=0;




char Check_Respond(char * Expected_Respond,char Respond_Length);

ISR (USART_RXC_vect)
{
	uint8_t oldsrg = SREG;
	cli();
	Rec_Data[Counter] = UDR;
	Counter++;
	if(Counter == DEFAULT_BUFFER_SIZE){
		Counter = 0; //pointer = 0;
	}
	SREG = oldsrg;
}


int main()
{
	char i=0,x=128,y=0,z=0,a=0,b=0,c=0,d=0;

	DDRD=(1<<PD4);
	init_UART();
	uart_init();
	sei();


	UART_SEND_string("ATE0\r\n");
	_delay_ms(1000);


	UART_SEND_string("AT+CWMODE=3\r\n");
	_delay_ms(3000);



	UART_SEND_string("AT+CIPMUX=0\r\n");
	_delay_ms(3000);


	UART_SEND_string("AT+CIPMODE=0\r\n");
	_delay_ms(3000);


	//
	//		UART_SEND_string("AT+CWJAP_DEF=\"Honor\",\"dodododo\"\r\n");
	UART_SEND_string("AT+CWJAP_DEF=\"Embeddedfab\",\"Embeddedfab135\"\r\n");

	_delay_ms(3000);
	_delay_ms(3000);
	_delay_ms(3000);
	_delay_ms(3000);
	_delay_ms(3000);


	UART_SEND_string("AT+CIPSTART=\"TCP\",\"mqtt.thingspeak.com\",1883\r\n");
	_delay_ms(3000);




	UART_SEND_string("AT+CIPSEND=30\r\n");
	_delay_ms(1000);

	UART_SendChar(0x10);
	UART_SendChar(0x1C);
	UART_SendChar(0x00);
	UART_SendChar(0x04);
	UART_SEND_string("MQTT");
	UART_SendChar(0x04);
	UART_SendChar(0x02);
	UART_SendChar(0x00);
	UART_SendChar(0x3C);
	UART_SendChar(0x00);
	UART_SendChar(0x10);
	UART_SEND_string("1GCN259YMUDE2JWR");

	_delay_ms(1000);

	UART_SEND_string("AT+CIPSEND=59\r\n");
	_delay_ms(1000);

	UART_SendChar(0x30);
	UART_SendChar(0x39);
	UART_SendChar(0x00);
	UART_SendChar(0x36);

	UART_SEND_string("channels/931047/publish/fields/field3/SD5OBD49N5H4O8RY");
	UART_SEND_string("8");



	return 0;
}



char Check_Respond(char * Expected_Respond,char Respond_Length)
{

	Counter=0;

	uart_TX_string("Respond\r\n");    //For Debug only
	uart_TX_string(Rec_Data);         //For Debug only
	uart_TX_string("END\r\n");        //For Debug only

	if(!strncmp(Rec_Data,Expected_Respond, Respond_Length))
	{
		uart_TX_string("Respond matched\r\n");   //For Debug only
		memset(Rec_Data,0,Respond_Length);
		return TRUE;
	}

	memset(Rec_Data,0,Respond_Length);
	return FALSE;


}








//
