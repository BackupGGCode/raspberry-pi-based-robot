#include "Communication/UART/SerialCommunication.h"

SerialCommunication::SerialCommunication()
{
    //bzero(&options, sizeof(options)); /* clear struct for new port settings */
}

SerialCommunication::~SerialCommunication()
{
    close(uart0_filestream);
    //tcsetattr(fd,TCSANOW,&oldtio);
    //dtor
}

bool SerialCommunication::ConnectPort()//const char *PortAddress, speed_t BaudRate
{
        //-------------------------
        //----- SETUP USART 0 -----
        //-------------------------
        //At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively


        //OPEN THE UART
        //The flags (defined in fcntl.h):
        //	Access modes (use 1 of these):
        //		O_RDONLY - Open for reading only.
        //		O_RDWR - Open for reading and writing.
        //		O_WRONLY - Open for writing only.
        //
        //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
        //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
        //											immediately with a failure status if the output can't be written immediately.
        //
        //	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
        uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
        if (uart0_filestream == -1)
        {
            //ERROR - CAN'T OPEN SERIAL PORT
            printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
            return false;
        }

        //CONFIGURE THE UART
        //The flags (defined in termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
        //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
        //	CSIZE:- CS5, CS6, CS7, CS8
        //	CLOCAL - Ignore modem status lines
        //	CREAD - Enable receiver
        //	IGNPAR = Ignore characters with parity errors
        //	ICRNL - Map CR to NL on input
        //	PARENB - Parity enable
        //	PARODD - Odd parity (else even)

        tcgetattr(uart0_filestream, &options);
        cfsetispeed(&options, B4800);					//<Set baud rate
        cfsetospeed(&options, B4800);					//<Set baud rate
        options.c_cflag = B4800 | CS8 | CLOCAL | CREAD;                 //<Set baud rate
        options.c_iflag = IGNPAR | ICRNL;
        options.c_oflag = 0;
        tcflush(uart0_filestream, TCIFLUSH);
        tcsetattr(uart0_filestream, TCSANOW, &options);

        return true;
}

bool SerialCommunication::TestPort()
{
    //----- TX BYTES -----
        unsigned char tx_buffer[20];
        unsigned char *p_tx_buffer;

        p_tx_buffer = &tx_buffer[0];
        *p_tx_buffer++ = 'H';
        *p_tx_buffer++ = 'e';
        *p_tx_buffer++ = 'l';
        *p_tx_buffer++ = 'l';
        *p_tx_buffer++ = 'o';

        if (uart0_filestream != -1)
        {
            int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write
            if (count < 0)
            {
                //printf("UART TX error\n");
                //ui->listWidget_2->addItem("UART TX error");
                return false;
            }
        }

        return true;
}

void SerialCommunication::ClosePort()
{
    close(uart0_filestream);
    //tcsetattr(fd,TCSANOW,&oldtio);
    //dtor
}

int SerialCommunication::SendString(const char *DataString)
{
    int DataStringLength=strlen(DataString);
    int bytes_written=0;
    bytes_written=write(uart0_filestream,DataString,DataStringLength);

    //printf("StringLength:%d bytes_written:%d\n",DataStringLength,bytes_written);
    if(bytes_written==-1)
    {
        perror("HIBA: Nem lehet írni a portra, adj írási engedéjt a portnak!");
        return -1;
    }

    if(bytes_written != DataStringLength)
    {
        perror("HIBA: Az adatok, csak részben kerültek a portra.\n Hiba a küldésnél.");
        return -2;
    }
    else
    {
        printf("Adat elküldve\n");
        return 1;
    }
}

int SerialCommunication::IsDataAviable()
{
    printf("\nVárakozás adatokra:\n");
    int bytes_read=0;
    //printf("%d\n",fd);
    bytes_read=read(uart0_filestream,buffer,500);// Végtelen ciklust indít önmagában - Várakozés adatokra
    buffer[bytes_read]='\0';// Sztring lezárása sztring vége karakterrel
    if(bytes_read == -1)
    {
        perror("HIBA: Nem lehet adatokat olvasni a portról!\nAdj olvasási engedéjt a portnak.");
        return -1;
    }

    if(!bytes_read)
    {
        perror("HIBA: A String üres!");
        return -2;
    }

    return 1;
}

void SerialCommunication::PrintData()
{
    printf("%s",buffer);
}


char* SerialCommunication::GetData()
{
    return buffer;
}






