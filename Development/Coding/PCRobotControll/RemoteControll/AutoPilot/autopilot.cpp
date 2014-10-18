#include "autopilot.h"
#include "ui_autopilot.h"

AutoPilot::AutoPilot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoPilot)
{
    ui->setupUi(this);
}

AutoPilot::~AutoPilot()
{
    delete ui;
}
