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

#include "stdlib.h"
#include "string.h"


#define Client_ID      "11232siy1weu1e21"        //16 digits
#define User_Name      "nmr"                     //3 digits
#define Password       "GXQD8VN78RAISAUH"        //MQTT Key

#define Channel_ID     "996736"                  //Your Channel ID
#define Write_Key      "RNNN90XKATASUZZG"        //Api Write Key
#define Data           "7"       				 //Data

#define Publish       1
#define Subscribe     0


#define TRUE 1
#define FALSE 0
#define DEFAULT_BUFFER_SIZE 100
char Rec_Data[DEFAULT_BUFFER_SIZE];
char Counter=0;


char Check_Respond(char * Expected_Respond);
char Check_Word_in_Respond(char * Word);
void Clear_REC_Buffer(void);


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
	sei();

	_delay_ms(1000);
	Clear_REC_Buffer();
	UART_SEND_string("ATE0\r\n");
	while(!((Check_Respond("\r\nOK\r\n"))||(Check_Respond("\r\nATE0\r\n\r\nOK\r\n"))))
	{
		_delay_ms(1);
	}


	UART_SEND_string("AT+CWMODE=3\r\n");
	while(!Check_Respond("\r\nOK\r\n"))
	{
		_delay_ms(1);
	}


	UART_SEND_string("AT+CIPMUX=0\r\n");
	while(!Check_Respond("\r\nOK\r\n"))
	{
		_delay_ms(1);
	}


	UART_SEND_string("AT+CIPMODE=0\r\n");
	while(!Check_Respond("\r\nOK\r\n"))
	{
		_delay_ms(1);
	}

	//
	//		UART_SEND_string("AT+CWJAP_DEF=\"Honor\",\"dodododo\"\r\n");
	UART_SEND_string("AT+CWJAP_DEF=\"Embeddedfab\",\"Embeddedfab135\"\r\n");

	while(!Check_Respond("WIFI DISCONNECT\r\nWIFI CONNECTED\r\nWIFI GOT IP\r\n\r\nOK\r\n"))
	{
		_delay_ms(1);
	}


	UART_SEND_string("AT+CIPSTART=\"TCP\",\"mqtt.thingspeak.com\",1883\r\n");
	while(!Check_Respond("CONNECT\r\n\r\nOK\r\n"))
	{
		_delay_ms(1);
	}



	UART_SEND_string("AT+CIPSEND=53\r\n");
	while(!Check_Respond("\r\nOK\r\n> "))
	{
		_delay_ms(1);
	}

	UART_SendChar(0x10);
	UART_SendChar(0x33);
	UART_SendChar(0x00);
	UART_SendChar(0x04);
	UART_SEND_string("MQTT");
	UART_SendChar(0x04);
	UART_SendChar(0xC2);
	UART_SendChar(0x00);
	UART_SendChar(0x3C);
	UART_SendChar(0x00);
	UART_SendChar(0x10);
	UART_SEND_string(Client_ID);
	UART_SendChar(0x00);
	UART_SendChar(0x03);
	UART_SEND_string(User_Name);
	UART_SendChar(0x00);
	UART_SendChar(0x10);
	UART_SEND_string(Password);

	while(!Check_Word_in_Respond("+IPD"))
	{
		_delay_ms(1);
	}
	_delay_ms(1000);
	Clear_REC_Buffer();



#if Publish

	UART_SEND_string("AT+CIPSEND=59\r\n");
	while(!Check_Respond("\r\nOK\r\n> "))
	{
		_delay_ms(1);
	}



	UART_SendChar(0x30);
	UART_SendChar(0x39);
	UART_SendChar(0x00);
	UART_SendChar(0x36);

	UART_SEND_string("channels/");
	UART_SEND_string(Channel_ID);
	UART_SEND_string("/publish/fields/field2/");
	UART_SEND_string(Write_Key);
	UART_SEND_string(Data);

#endif

#if Subscribe

	UART_SEND_string("AT+CIPSEND=46\r\n");
	while(!Check_Respond("\r\nOK\r\n> "))
	{
		_delay_ms(1);
	}


	UART_SendChar(0x82);
	UART_SendChar(0x2c);
	UART_SendChar(0x00);
	UART_SendChar(0x0A);
	UART_SendChar(0x00);
	UART_SendChar(0x27);
	UART_SEND_string("channels/");
	UART_SEND_string(Channel_ID);
	UART_SEND_string("/subscribe/fields/field3");
	UART_SendChar(0x00);





#endif



	return 0;
}


char Check_Respond(char * Expected_Respond)
{
	char Respond_Length=0;

	Respond_Length=strlen(Expected_Respond);

	if(strncmp(Rec_Data,Expected_Respond, Respond_Length)==0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}
	return FALSE;


}


char Check_Word_in_Respond(char * Word)
{


	if(strstr(Rec_Data,Word) != 0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}

	return FALSE;
}

void Clear_REC_Buffer(void)
{
	Counter=0;
	memset(Rec_Data,0,DEFAULT_BUFFER_SIZE);
}







//
