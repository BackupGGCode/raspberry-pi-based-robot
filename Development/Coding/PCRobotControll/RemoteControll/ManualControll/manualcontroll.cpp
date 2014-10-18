#include "manualcontroll.h"
#include "ui_manualcontroll.h"

ManualControll::ManualControll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualControll)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);

    ui->dial->setRange(-90,90);
    ui->dial->setValue(0);

    ui->dial_PWM->setRange(0,100);
    ui->dial_PWM->setValue(0);

    connect(&connectionOverTCP_, SIGNAL(PipeOutSignal(QString)),this, SLOT(GetRobotAnswers(QString)));

    isPressed_ = false;
    isReleased_ = false;
    prevSet_ = Qt::Key_0;
    keyTimer_.start(300);
    connect(&keyTimer_,SIGNAL(timeout()),this,SLOT(KeyFilter()));
}

ManualControll::~ManualControll()
{
    delete ui;
}


void ManualControll::GetRobotAnswers(QString answer)
{
    ui->listWidget->addItem(answer);
}


void ManualControll::ChangeSettings(QString IP, QString Port)
{
    connectionOverTCP_.start(IP, Port.toInt());

    if(connectionOverTCP_.getConnectionState() == true)
    {
        ui->listWidget->addItem("Csatlakozva a Robothoz!");
    }
    else
    {
        //ui->listWidget->addItem("Nem lehet csatlakozni!");
    }
}


bool ManualControll::IsConnected()
{
    return connectionOverTCP_.getConnectionState();
}


void ManualControll::send_stop()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        //ui->ConnectionStateLabel->setText("Connected to Server");

        Message_.clear();// Delete previous message
        Message_.append("stop");

        connectionOverTCP_.startTransfer(Message_);
        ui->listWidget->addItem(Message_);
    }
    else
    {
        //ui->ConnectionStateLabel->setText("Not Connected to Server");
        ui->listWidget->addItem("Sikertelen kuldes: Stop !");
    }
}

void ManualControll::on_forward_pressed()
{
    //qDebug() << "1";
    if(connectionOverTCP_.getConnectionState() == true)
    {
        //ui->ConnectionStateLabel->setText("Connected to Server");

        Message_.clear();// Delete previous message
        Message_.append("forward");

        connectionOverTCP_.startTransfer(Message_);
        ui->listWidget->addItem(Message_);
    }
    else
    {
        //ui->ConnectionStateLabel->setText("Not Connected to Server");
        ui->listWidget->addItem("Sikertelen kuldes: Elore !");
    }
}


void ManualControll::on_forward_clicked()
{
    send_stop();
}

void ManualControll::on_left_pressed()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        //ui->ConnectionStateLabel->setText("Connected to Server");

        Message_.clear();// Delete previous message
        Message_.append("left");

        connectionOverTCP_.startTransfer(Message_);
        ui->listWidget->addItem(Message_);
    }
    else
    {
        //ui->ConnectionStateLabel->setText("Not Connected to Server");
        ui->listWidget->addItem("Sikertelen kuldes: Balra !");
    }
}

void ManualControll::on_left_clicked()
{
    send_stop();
}

void ManualControll::on_right_pressed()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        //ui->ConnectionStateLabel->setText("Connected to Server");

        Message_.clear();// Delete previous message
        Message_.append("right");

        connectionOverTCP_.startTransfer(Message_);
        ui->listWidget->addItem(Message_);
    }
    else
    {
        //ui->ConnectionStateLabel->setText("Not Connected to Server");
        ui->listWidget->addItem("Sikertelen kuldes: Jobbra !");
    }
}

void ManualControll::on_right_clicked()
{
    send_stop();
}

void ManualControll::on_backward_pressed()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        //ui->ConnectionStateLabel->setText("Connected to Server");

        Message_.clear();// Delete previous message
        Message_.append("backward");

        connectionOverTCP_.startTransfer(Message_);
        ui->listWidget->addItem(Message_);
    }
    else
    {
        //ui->ConnectionStateLabel->setText("Not Connected to Server");
        ui->listWidget->addItem("Sikertelen kuldes: Hatra !");
    }
}

void ManualControll::on_backward_clicked()
{
    send_stop();
}


void ManualControll::on_dial_sliderReleased()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        Message_.clear();
        Message_.append("Servo:");
        Message_.append(QString::number(ui->dial->value()));//Szervo motor pozició

        connectionOverTCP_.startTransfer(Message_);
        ui->listWidget->addItem(Message_);
    }
    else
    {
        //ui->ConnectionStateLabel->setText("Not Connected to Server");
        ui->listWidget->addItem("Sikertelen kuldes: Servo !");
    }
}

void ManualControll::on_dial_PWM_sliderReleased()
{
    //qDebug() << "3";

    if(connectionOverTCP_.getConnectionState() == true)
    {
        Message_.clear();
        Message_.append("PWM:");
        Message_.append(QString::number(ui->dial_PWM->value()));//DC Motor sebesség - Kitöltési tényező

        connectionOverTCP_.startTransfer(Message_);
        ui->listWidget->addItem(Message_);
    }
    else
    {
        //ui->ConnectionStateLabel->setText("Not Connected to Server");
        ui->listWidget->addItem("Sikertelen kuldes: PWM !");
    }
}

void ManualControll::keyPressEvent(QKeyEvent *event)
{
    key_ = (Qt::Key)event->key();
    isPressed_ = true;
}

void ManualControll::keyReleaseEvent(QKeyEvent *event)
{
    key_ = (Qt::Key)event->key();
    isReleased_ = true;
}

void ManualControll::KeyFilter()
{
    bool isFirst = false;

    if((isReleased_ == false) && (isPressed_ == false))
    {

        if(prevSet_ != Qt::Key_0)
        {
            prevSet_ = Qt::Key_0;//Ezzel jelzem most hogy megszakadt a nyomvatartás
            send_stop();            
            qDebug() << "stop1";
        }

    }
    else if(isPressed_ == true)
    {
        if(prevSet_ == Qt::Key_0)//A legutóbbi felengedés óta ez az első lenyomás?
        {
            isFirst = true;
        }

        if(prevSet_ != key_)
        {
            if(key_ == Qt::Key_A)
            {
                on_left_pressed();
                qDebug() << 'A';
            }
            else if(key_ == Qt::Key_S)
            {
                on_backward_pressed();
                qDebug() << 'S';
            }
            else if(key_ == Qt::Key_D)
            {
                on_right_pressed();
                qDebug() << 'D';
            }
            else if(key_ == Qt::Key_W)
            {
                on_forward_pressed();
                qDebug() << 'W';
            }
        }

        prevSet_ = key_;
    }
    else if(isReleased_ == true)
    {
        if(prevSet_ != Qt::Key_0)
        {
            prevSet_ = Qt::Key_0;
            send_stop();
            qDebug() << "stop2";
        }
    }



    if(isFirst == false)
    {
        isPressed_ = false;
        isReleased_ = false;
    }

}

void ManualControll::on_resetButton_clicked()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        connectionOverTCP_.startTransfer("Reset");
        ui->listWidget->addItem("Reset");
    }
    else
    {
        ui->listWidget->addItem("Nem lehet resetelni a robotot!");
    }
}

void ManualControll::on_offButton_clicked()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        connectionOverTCP_.startTransfer("Off");
        ui->listWidget->addItem("Kikapcsolva");
    }
    else
    {
        ui->listWidget->addItem("Nem lehet lea'llitani a robotot!");
    }
}

void ManualControll::on_quitButton_clicked()
{
    if(connectionOverTCP_.getConnectionState() == true)
    {
        connectionOverTCP_.startTransfer("Quit");
        ui->listWidget->addItem("Quit");
    }
    else
    {
        ui->listWidget->addItem("Nem lehet kile'pni a programbol!");
    }
}
