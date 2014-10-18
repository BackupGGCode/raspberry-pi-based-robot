#include "controllpanel.h"
#include "ui_controllpanel.h"

ControllPanel::ControllPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControllPanel)
{
    ui->setupUi(this);
    Display_.hide();
    ui->startButton->hide();
    ui->Cam_fpsBox->setValue(2);
    ui->sensorLabel->setStyleSheet("QLabel { background-color : gray; color : black; }");
    ui->cameraLabel->setStyleSheet("QLabel { background-color : gray; color : black; }");
    ui->rpiLabel->setStyleSheet("QLabel { background-color : gray; color : black; }");
    ui->motorLabel->setStyleSheet("QLabel { background-color : gray; color : black; }");

    connect(&Display_,SIGNAL(GoBackToMainMenu()),this,SLOT(ReturnToMainMenu()));
    connect(&Display_,SIGNAL(exitProgram()),this,SLOT(exitProgram()));
}

ControllPanel::~ControllPanel()
{
    delete ui;
}

void ControllPanel::on_startButton_clicked()
{
    this->hide();
    Display_.showMaximized();
    manualControll_.show();
    manualControll_.raise();
}

void ControllPanel::on_connectButton_clicked()
{
    ui->startButton->show();

    //Kapcsolódás indítása

    //Mobil telefon
    if(Display_.IsConnected() == true)
    {
        ui->sensorLabel->setText("Online");
        ui->sensorLabel->setStyleSheet("QLabel { background-color : green; color : black; }");
    }else{
        ui->sensorLabel->setText("Offline");
        ui->sensorLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

    //Kamera
    on_cameraButton_clicked();
    if(Display_.cameraIsConnected() == true)
    {
        ui->cameraLabel->setText("Online");
        ui->cameraLabel->setStyleSheet("QLabel { background-color : green; color : black; }");
    }else{
        ui->cameraLabel->setText("Offline");
        ui->cameraLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
    }
    //Visszaellenőrzés és label beállítása

    //RPI
    on_rpiButton_clicked();
    if(manualControll_.IsConnected() == true)
    {
        ui->rpiLabel->setText("Online");
        ui->rpiLabel->setStyleSheet("QLabel { background-color : green; color : black; }");
    }else{
        ui->rpiLabel->setText("Offline");
        ui->rpiLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

}

void ControllPanel::on_cameraButton_clicked()
{
    Display_.cameraSettings(ui->Cam_IP_Edit->text(),ui->Cam_Port_Edit->text(),ui->Cam_fpsBox->value());
}

void ControllPanel::on_rpiButton_clicked()
{
    manualControll_.ChangeSettings(ui->RPI_IP_Edit->text(),ui->RPI_Port_Edit->text());
}

void ControllPanel::ReturnToMainMenu()
{
    this->show();
    Display_.hide();
    manualControll_.hide();
}

void ControllPanel::exitProgram()
{
    this->close();
    Display_.close();
    manualControll_.close();
}
