/*
4800 baud, Nincs Paritas Bit, 1 Stop Bit, Flow Control = NONE
*/
 
#define F_CPU 1000000UL // rendszer orajel: 1 MHz
#define USART_BAUDRATE 4800 // soros kommunikacio sebessege: 4800 bps
#define UBRR_ERTEK ((F_CPU / (USART_BAUDRATE * 16UL)) - 1) // UBRR
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "motor.h"
#include "uart.h"  
#include <stdio.h>

volatile Message Command = {.PWM=0, .Direction='e'};
 
//________________________________________________________________________
void  execution()
{

	if((Command.PWM<0)||(Command.PWM>101))
	{
		UARTStringKuld("Hiba! : Nem megfelel� PWM �rt�k!\n *");
		return;
	}


	if(Command.Direction == 'e')
	{
		hatra(Command.PWM);	
	}
	else if(Command.Direction == 'g')
	{
		fordul_bal(Command.PWM);
	}
	else if(Command.Direction == 'f')
	{
		fordul_jobb(Command.PWM);
	}
	else if(Command.Direction == 'h')
	{
		elore(Command.PWM);
	}
	else if(Command.Direction == 'i')
	{
		motor_ki();
	}
	else{
		UARTStringKuld("Hiba! : Nem megfelel� ir�ny �rt�k!\n *");
		return;
	}


	UARTStringKuld("�zenet fogadva! *");
	UARTAdatKuld('[');
	UARTAdatKuld(Command.Direction);
	UARTAdatKuld(']');
	UARTAdatKuld('\n');


}


//_______________________________________________________________________
int main(void) 			// Foprogram
{

   KonfigUART();  		// UART Konfiguralasa
   sei();    			// Altalanos megszakitasok engedelyezese

 
   while(1) 			// Vegtelen ciklus
   {
   }

   return 0;
}


//________________________________________________________________________

ISR(USART_RXC_vect)  // RX interrupt, ezek az utasitasok futak le ha adat erkezik a TX vonalon
{
	char Data = UARTAdatFogad();     // A berekezo bajt fogadasa

	if(Data < 101) // Ez egy kit�lt�si t�nyez� m�dos�t� �zenet
	{
		Command.PWM = Data;
	}
	else // Ez egy ir�ny m�dos�t� �zenet
	{
		Command.Direction = Data;
	}

	execution();
}


