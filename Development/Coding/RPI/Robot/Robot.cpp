#include "Robot.h"

Robot::Robot()
{
    connect(&ComManager_,SIGNAL(exitProgramm()),this,SLOT(Quit()));
}

void Robot::Quit()
{
    loop_->quit();
}

void Robot::GetEventLoop(QCoreApplication *loop)
{
    loop_ = loop;
}
