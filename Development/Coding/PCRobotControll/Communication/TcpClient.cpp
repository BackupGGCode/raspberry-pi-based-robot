#include "TcpClient.h"
#include <QtNetwork/QHostAddress>

TcpClient::TcpClient(QObject* parent): QObject(parent)
{
  //connect(&client, SIGNAL(connected()),
    //this, SLOT(startTransfer()));

    connect(&Socket_, SIGNAL(connected()),this, SLOT(setConnectionStateOn()));
    //connect(&client, SIGNAL(disconnected()),this, SLOT(setConnectionStateOff()));

    connect(&Socket_, SIGNAL(readyRead()),this, SLOT(startRead()));


  IsConnected_ = false;
}

TcpClient::~TcpClient()
{
  Socket_.close();
}

void TcpClient::start(QString address, quint16 port)
{
  //address="192.168.2.102";
  //port=8888;
  //qDebug() << "1";
  QHostAddress addr(address);
  //qDebug() << "2";
  Socket_.connectToHost(addr, port);
  //qDebug() << "3";
}

void TcpClient::startTransfer(QString messageContent)
{
    if(messageContent.length() > 0){
        Socket_.write(messageContent.toAscii(), 1000);
    }
}

void TcpClient::startRead()
{
  qint64 ExpectedIncomeDataSize = Socket_.bytesAvailable();

  if(ExpectedIncomeDataSize < 2){return;}

  char *buffer = new char[ExpectedIncomeDataSize];
  //char buffer[10000] = {0};
  qint64 IncomeDataSize = Socket_.read(buffer, ExpectedIncomeDataSize);
  //qDebug() << buffer;

  if(ExpectedIncomeDataSize != IncomeDataSize)
  {
      delete[] buffer;
      return;
  }

  QString MessageData(buffer);

  delete[] buffer;

  PipeOutSignal(MessageData);

  qDebug() << MessageData << "\n";
  // Adatok kinyerése és elmentése:
}


void TcpClient::setConnectionStateOn(){
    IsConnected_ = true;
}

//void Client::setConnectionStateOff(){
//    IsConnected = false;
//}

bool TcpClient::getConnectionState(){
    return IsConnected_;
}
