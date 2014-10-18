#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer: public QObject
{
Q_OBJECT
public:
  TcpServer(QObject * parent = 0);
  ~TcpServer();

public:
  QTcpServer Server_;
  QTcpSocket* Socket_;
  void Answer(QString answer);

public slots:
  void acceptConnection();
  void startRead();
  void closeConnection();

signals:
    void PipeOutSignal(QString Command);

};

#endif // TCPSERVER_H
