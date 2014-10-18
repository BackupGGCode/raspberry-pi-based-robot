#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "Communication/ComManager/Commanager.h"

class Robot : public QObject
{
Q_OBJECT

public:
    Robot();
    ComManager ComManager_;
    QCoreApplication* loop_;
    void GetEventLoop(QCoreApplication* loop);

public slots:
    void Quit();

};

#endif // ROBOT_H
