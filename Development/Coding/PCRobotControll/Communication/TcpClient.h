#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>


class TcpClient: public QObject
{
Q_OBJECT
public:
  TcpClient(QObject* parent = 0);
  ~TcpClient();
  void start(QString address, quint16 port);

public slots:
    bool getConnectionState();
    void startTransfer(QString messageContent);

private:
    bool IsConnected_;
      QTcpSocket Socket_;

private slots:
    void setConnectionStateOn();
    //void setConnectionStateOff();
    void startRead();

signals:
    void PipeOutSignal(QString Answer);

};

#endif // TCPCLIENT_H
