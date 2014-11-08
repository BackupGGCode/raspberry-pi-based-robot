#include <avr/io.h>
#include <stdlib.h>

void KonfigUART()  // UART beallitasa
{
    // 4800 bps soros kommunikacio sebesseg beallitasa
    UBRRL = UBRR_ERTEK;        // UBRR_ERTEK also 8 bitjenek betoltese az UBRRL regiszterbe
    UBRRH = (UBRR_ERTEK>>8);   // UBRR_ERTEK felso 8 bitjenek betoltese az UBRRH regiszterbe
   // Aszinkron mod, 8 Adat Bit, Nincs Paritas Bit, 1 Stop Bit
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
   //Ado es Vevo aramkorok bekapcsolasa + az RX interrupt engedelyezese
    UCSRB |= (1 << RXEN) | (1 << RXCIE) | (1 << TXEN);   //
}

 
char UARTAdatFogad() // Ez a fuggveny a beerkezo adatokat kiolvassa az UDR regiszter bejovo pufferebol
{
   while(!(UCSRA & (1<<RXC))) // Varakozas amig nincs uj bejovo adat
   {
      //  Varakozas
   }
   //Most mar van beerkezett adat, amit kiolvasunk a pufferbol
   return UDR;
}

 
void UARTAdatKuld(char data) // Ez a fuggveny a kuldendo adatot beirja az UDR regiszter kimeno pufferjebe
{
   while(!(UCSRA & (1<<UDRE)))  // Varakozas amig az Ado kesz nem lesz az adatkuldesre
   {
      //  Varakozas
   }
   // Az Ado mar kesz az adatkuldesre, a kuldendo adatot a kimeno pufferjebe irjuk
   UDR=data;
}

void UARTStringKuld(char* data) // Ez a fuggveny a kuldendo adatot beirja az UDR regiszter kimeno pufferjebe
{  

   for(int i=0;data[i] != '*'; i++)
   {
   		   while(!(UCSRA & (1<<UDRE)))  // Varakozas amig az Ado kesz nem lesz az adatkuldesre
   			{
     		 //  Varakozas
   			}
   			// Az Ado mar kesz az adatkuldesre, a kuldendo adatot a kimeno pufferjebe irjuk
   			UDR=data[i];
			
			if(i>100){break;}// Túl olvasás elleni védelem 
   }
}

typedef struct Message{
int PWM;
char Direction;
}Message;
