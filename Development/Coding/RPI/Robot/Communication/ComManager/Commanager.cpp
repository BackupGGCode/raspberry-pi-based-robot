#include "Commanager.h"

ComManager::ComManager()
{
    UartState_ = false;

    UartState_ = UART_.ConnectPort();

    connect(&TcpServer_, SIGNAL(PipeOutSignal(QString)),this, SLOT(execute(QString)));
}

bool ComManager::IsUartConneceted()
{
    return UartState_;
}


void ComManager::execute(QString Command)
{
    char ConvertedMessage = 0;


    if(Command.contains("forward")){ // -------------------- Nagyobb mint 100 a karakter értéke
        ConvertedMessage = 'e';
    }else if(Command.contains("right")){
        ConvertedMessage = 'f';
    }else if(Command.contains("left")){
        ConvertedMessage = 'g';
    }else if(Command.contains("backward")){
        ConvertedMessage = 'h';
    }else if(Command.contains("stop")){
        ConvertedMessage = 'i';
    }else if(Command.contains("PWM")){// ------------------- Kissebb mint 100 a karakter decimális értéke

        QStringList itemSL = QString(Command).split(":");

        if(itemSL.size() == 2)// Mivel 2 elemre számítok!
        {
            ConvertedMessage = (char) QString(itemSL[1]).toInt();
        }else{
            SendErrorMessage("A PWM adat rossz forma'tumban e'rkezett!");
            TcpServer_.Answer("A PWM adat rossz forma'tumban e'rkezett!");
        }

    }else if(Command.contains("Servo")){

    }else if(Command.contains("Off")){

        if(system("halt"))
        {
            TcpServer_.Answer("A lea'llitas ve'grehajtva!");
        }
        else
        {
            TcpServer_.Answer("Nem ve'grehajthato' a lea'llitas!");
        }

        return;

    }else if(Command.contains("Reset")){

        if(system("reboot"))
        {
            TcpServer_.Answer("Az u'jraindita's ve'grehajtva!");
        }
        else
        {
            TcpServer_.Answer("Nem ve'grehajthato' az u'jraindita's!");
        }

        return;

    }else if(Command.contains("Quit")){

        TcpServer_.Answer("Kile'pe's a programból!");

        exitProgramm();

        return;

    }else{
        // Valamilyen hiba
    }

    if(IsUartConneceted())
    {
        char Msg[2] = {ConvertedMessage, '\0'};

        if(UART_.SendString(Msg)){
            SendErrorMessage("Üzenet tova'bbi'tva az UART portra!");
            TcpServer_.Answer("Üzenet tova'bbi'tva az UART portra!");
        }else{
            SendErrorMessage("Sikerült ele'rni az UART-ot, viszont hiba le'pett fel a külde'skor az UART-on!");
            TcpServer_.Answer("Sikerült ele'rni az UART-ot, viszont hiba le'pett fel a külde'skor az UART-on!");
        }
    }else{
        SendErrorMessage("Az UART nem e'rheto\" el!");
        TcpServer_.Answer("Az UART nem e'rheto\" el!");
    }

}
