#include "Communication/TCP/TcpServer.h"
#include <iostream>
using namespace std;

TcpServer::TcpServer(QObject* parent): QObject(parent)
{
  connect(&Server_, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));

  Server_.listen(QHostAddress::Any, 8888);
}

TcpServer::~TcpServer()
{
  Server_.close();
}

void TcpServer::acceptConnection()
{
  qDebug()<<"New Connection";
  Socket_ = Server_.nextPendingConnection();

  connect(Socket_, SIGNAL(readyRead()),
    this, SLOT(startRead()));
}

void TcpServer::startRead()
{
  qint64 ExpectedIncomeDataSize = Socket_->bytesAvailable();

  if(ExpectedIncomeDataSize < 2){return;}

  char *buffer = new char[ExpectedIncomeDataSize];
  //char buffer[10000] = {0};
  qint64 IncomeDataSize = Socket_->read(buffer, ExpectedIncomeDataSize);
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

void TcpServer::Answer(QString answer)
{

    if(answer.length() > 0)
    {
        Socket_->write(answer.toAscii(), 1000);
    }

}

void TcpServer::closeConnection()
{
   Socket_->close(); // Ezért nem marad nyitva a socket és nem megy wite-al is az írás.
}
