#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <SensorData/sensorsdataformat.h>

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

private:
  SensorsDataFormat SensorData;

signals:
    void PipeOutSignal(const SensorsDataFormat& SensorsData);

};

#endif // TCPSERVER_H
