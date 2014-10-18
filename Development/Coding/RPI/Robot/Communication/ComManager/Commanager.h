#ifndef COMMANAGER_H
#define COMMANAGER_H

#include "Communication/UART/SerialCommunication.h"
#include "Communication/TCP/TcpServer.h"

class ComManager : public QObject
{
Q_OBJECT

public:
    ComManager();
    bool IsUartConneceted();


public slots:
     //Majd void helyett int kell és hiba esetén a hibakóddal térjen vissza:
     void execute(QString Command);

private:
     SerialCommunication UART_;
     TcpServer TcpServer_;
     bool UartState_;

signals:
     void SendErrorMessage(QString Msg);
     void exitProgramm();
};

#endif // COMMANAGER_H
