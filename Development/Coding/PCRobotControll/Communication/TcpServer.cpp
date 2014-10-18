#include "Communication/TcpServer.h"
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
  //qDebug() << Socket_->peerAddress(); // Ezzel a kliens IP címe lekérdezhető.

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
  QStringList sensorSL = MessageData.split("|");

  //Néha hibás sztring jön át (zaj / hiba ...) Ez a feltétel, abban az esetben fontos!!!
  //Tehát, mivel néha nem az jön át mint amire számítok fontos hogy leelenőrizzem, mivel előre megadott indexekre
  // hivatkozok, holott nem is bisztos, hogy van 6.-ik elem a tömben, ha a zaj miatt csak 1 karakter jött át a sztringből!
  if(sensorSL.size() > 5)// Mivel 6 elemre számítok!
  {
      QStringList itemSL = QString(sensorSL[0]).split("/");

      if(itemSL.size() > 2)// Mivel 3 elemre számítok!
      {
          SensorData.Accelerometer_RealSensor.x = QString(itemSL[0]).toDouble();
          SensorData.Accelerometer_RealSensor.y = QString(itemSL[1]).toDouble();
          SensorData.Accelerometer_RealSensor.z = QString(itemSL[2]).toDouble();
      }// Különben, meg úgy is nullával van feltöltve a tároló

      itemSL = QString(sensorSL[1]).split("/");

      if(itemSL.size() > 2)// Mivel 3 elemre számítok!
      {
          SensorData.Magnetometer_RealSensor.x = QString(itemSL[0]).toDouble();
          SensorData.Magnetometer_RealSensor.y = QString(itemSL[1]).toDouble();
          SensorData.Magnetometer_RealSensor.z = QString(itemSL[2]).toDouble();
      }

      itemSL = QString(sensorSL[2]).split("/");

      if(itemSL.size() > 2)// Mivel 3 elemre számítok!
      {
          SensorData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisX = QString(itemSL[0]).toDouble();
          SensorData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisY = QString(itemSL[1]).toDouble();
          SensorData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisZ = QString(itemSL[2]).toDouble();
      }

      SensorData.Ambientlightsensor_RealSensor.LightLevel = QString(sensorSL[3]).toDouble();

      SensorData.Proximitysensor_RealSensor.IsClose = QString(sensorSL[4]).toDouble();

      SensorData.Lineracceleration_VirtualSensor.LinearAcceleration = QString(sensorSL[5]).toDouble();

  }

  delete[] buffer;

  PipeOutSignal(SensorData);

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
