#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

        #include <sys/types.h>
        #include <sys/stat.h>
        #include <fcntl.h>
        #include <termios.h>
        #include <stdio.h>
        #include <string.h>
        #include <stdlib.h>
        #include <unistd.h>


        /* baudrate settings are defined in <asm/termbits.h>, which is
        included by <termios.h> */
        //#define BAUDRATE B38400
        /* change this definition for the correct port */
        #define RS232PORT "/dev/ttyS1"
        #define USBPORT "/dev/ttyUSB0"
        #define UART "/dev/ttyAMA0"
        #define _POSIX_SOURCE 1 /* POSIX compliant source */



class SerialCommunication
{
public:
    SerialCommunication();
    virtual ~SerialCommunication();


private:
        char buffer[501];// Statikus,-> az egyszerre átküldött legnagyobb mondatnál kell nagyobbnak lennie
        struct termios options;
        int uart0_filestream;


public:
//Váltani Serial portrol USB-re vagy fordítva..
        bool ConnectPort();//const char * PortAddress, speed_t BaudRate
        bool TestPort();
        void ClosePort();

//Adatok küldése/fogadása Stringként :
        int SendString(const char* DataString);
        int IsDataAviable();//Mérettel tér vissza
        void PrintData();// Sztring kiiratása printf()-el képernyőre - teszteléshez
        char* GetData();// String átadása
};

#endif // SERIALCOMMUNICATION_H
