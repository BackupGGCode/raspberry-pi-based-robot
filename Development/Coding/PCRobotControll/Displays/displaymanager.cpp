#include "displaymanager.h"
#include "ui_displaymanager.h"

DisplayManager::DisplayManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayManager)
{
    ui->setupUi(this);

    ui->verticalLayout->addWidget(&cameraView_);
    ui->verticalLayout->addWidget(&cubeView_);
    ui->verticalLayout->addWidget(&graphView_);

    //this->cameraView_.hide();
    this->cubeView_.hide();
    this->graphView_.hide();

    ui->menuButton->hide();

    connect(&TcpServer_.Server_, SIGNAL(newConnection()),
      this, SLOT(connectionSucces()));

  srand(QDateTime::currentDateTime().toTime_t());

  graphView_.setInteractions(QCustomPlot::iRangeDrag | QCustomPlot::iRangeZoom | QCustomPlot::iSelectAxes |
                                  QCustomPlot::iSelectLegend | QCustomPlot::iSelectPlottables | QCustomPlot::iSelectTitle);
  graphView_.setRangeDrag(Qt::Horizontal|Qt::Vertical);
  graphView_.setRangeZoom(Qt::Horizontal|Qt::Vertical);
  graphView_.xAxis->setRange(-8, 8);
  graphView_.yAxis->setRange(-5, 5);
  graphView_.setupFullAxesBox();
  graphView_.setTitle("Adatok");
  graphView_.xAxis->setLabel("t[ms]");
  graphView_.yAxis->setLabel("Present value");
  graphView_.legend->setVisible(true);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  graphView_.legend->setFont(legendFont);
  graphView_.legend->setSelectedFont(legendFont);
  graphView_.legend->setSelectable(QCPLegend::spItems); // legend box shall not be selectable, only legend items

  graphView_.addGraph();
  graphView_.graph(0)->setPen(QPen(Qt::blue));
  graphView_.addGraph();
  graphView_.graph(1)->setPen(QPen(Qt::red));
  graphView_.addGraph();
  graphView_.graph(2)->setPen(QPen(Qt::green));

  connectionState_ = false;

}

DisplayManager::~DisplayManager()
{
    cubeView_.close();
    delete ui;
}

void DisplayManager::connectionSucces()
{
    connectionState_ = true;
    //ui->connectLabel->setText("Van kapcsolat a robottal.");
    //connect(TCPserver.client, SIGNAL(readyRead()), this, SLOT(newIncomeData()));
}

bool DisplayManager::IsConnected()
{
    return connectionState_;
}

bool DisplayManager::cameraIsConnected()
{
    return cameraView_.IsConnected();
}

void DisplayManager::ActivateDisplay(DisplayType Selected)
{
    cameraView_.Stop();
    cameraView_.hide();
    cubeView_.hide();
    graphView_.hide();


    if(Selected == DisplayManager::Camera)
    {
        cameraView_.show();
        cameraView_.Start();
    }
    else if(Selected == DisplayManager::Graph)
    {
        graphView_.show();
    }
    else if(Selected == DisplayManager::OpenGL)
    {
        cubeView_.show();
    }
}

// Ez kell az adatok szétvállogatásához :
// http://qt-project.org/forums/viewthread/13336

void DisplayManager::on_AccelButton_clicked()
{
    ActivateDisplay(DisplayManager::Graph);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Konténer kiürítése:
    intiGraph();// Arra az esetre, ha más szenzorról váltanánk erre a szenzorra.


    // Megjelnítési paraméterek átalakítása gyorsulási adatokhoz
    // give the axes some labels:
    graphView_.xAxis->setLabel("t[ms]");
    graphView_.yAxis->setLabel("Acceleration");
    // set axes ranges, so we see all data:
    graphView_.xAxis->setRange(0, 25);
    graphView_.yAxis->setRange(-40, 40);
    graphView_.replot();

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlotA(const SensorsDataFormat&)));

    /*
    graphView_.addGraph();
    graphView_.graph(0)->setPen(QPen(Qt::blue));
    graphView_.addGraph();
    graphView_.graph(1)->setPen(QPen(Qt::red));
    graphView_.addGraph();
    graphView_.graph(2)->setPen(QPen(Qt::green));
    */

    graphView_.graph(0)->setName("X Axis");
    graphView_.graph(1)->setName("Y Axis");
    graphView_.graph(2)->setName("Z Axis");

}

void DisplayManager::PipeInSlotA(const SensorsDataFormat& SensorsData)
{
    // Ha másodpercenként 5 adat érkezik és 5mpes időintervallumban kell ábrázolni
    // Az 25 pontot jelent.
    //qDebug() << SensorsData.Accelerometer_RealSensor.x;


    // Csak egy elemet hozzá kell adni push-al és az elsőt törölne earsel:
    // http://www.cplusplus.com/reference/stl/vector/erase/

    x.push_back(SensorsData.Accelerometer_RealSensor.x);
    y.push_back(SensorsData.Accelerometer_RealSensor.y);
    z.push_back(SensorsData.Accelerometer_RealSensor.z);


    graphView_.graph(0)->setData(t, x);
    graphView_.graph(1)->setData(t, y);
    graphView_.graph(2)->setData(t, z);
    graphView_.replot();

    // A 25 elemmel ezelőtti infókat dobja el:
    if(x.size()>25){x.erase (x.begin(),x.begin()+1);}
    if(y.size()>25){y.erase (y.begin(),y.begin()+1);}
    if(z.size()>25){z.erase (z.begin(),z.begin()+1);}
}

void DisplayManager::on_LinearButton_clicked()
{
    ActivateDisplay(DisplayManager::Graph);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Konténer kiürítése:
    intiGraph();// Arra az esetre, ha más szenzorról váltanánk erre a szenzorra.


    // Megjelnítési paraméterek átalakítása gyorsulási adatokhoz
    // give the axes some labels:
    graphView_.xAxis->setLabel("t[ms]");
    graphView_.yAxis->setLabel("Linear Acceleration");
    // set axes ranges, so we see all data:
    graphView_.xAxis->setRange(0, 25);
    graphView_.yAxis->setRange(-40, 40);
    graphView_.replot();

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlotL(const SensorsDataFormat&)));

    graphView_.graph(0)->setName("Linear Acceleration");
    graphView_.graph(1)->setName(" ");
    graphView_.graph(2)->setName(" ");

}

void DisplayManager::PipeInSlotL(const SensorsDataFormat& SensorsData)
{
    x.push_back(SensorsData.Lineracceleration_VirtualSensor.LinearAcceleration);

    graphView_.graph(0)->setData(t, x);
    graphView_.graph(1)->setData(t, y);
    graphView_.graph(2)->setData(t, z);
    graphView_.replot();

    if(x.size()>25){x.erase (x.begin(),x.begin()+1);}
}


void DisplayManager::on_MagButton_clicked()
{
    ActivateDisplay(DisplayManager::Graph);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Konténer kiürítése:
    intiGraph();// Arra az esetre, ha más szenzorról váltanánk erre a szenzorra.


    // Megjelnítési paraméterek átalakítása gyorsulási adatokhoz
    // give the axes some labels:
    graphView_.xAxis->setLabel("t[ms]");
    graphView_.yAxis->setLabel("Magneto");
    // set axes ranges, so we see all data:
    graphView_.xAxis->setRange(0, 25);
    graphView_.yAxis->setRange(-0.1, 0.1);
    graphView_.replot();

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlotM(const SensorsDataFormat&)));

    graphView_.graph(0)->setName("X Axis");
    graphView_.graph(1)->setName("Y Axis");
    graphView_.graph(2)->setName("Z Axis");
}

void DisplayManager::PipeInSlotM(const SensorsDataFormat& SensorsData)
{
    // Ha másodpercenként 5 adat érkezik és 5mpes időintervallumban kell ábrázolni
    // Az 25 pontot jelent.
    //qDebug() << SensorsData.Accelerometer_RealSensor.x;


    // Csak egy elemet hozzá kell adni push-al és az elsőt törölne earsel:
    // http://www.cplusplus.com/reference/stl/vector/erase/

    x.push_back(SensorsData.Magnetometer_RealSensor.x);
    y.push_back(SensorsData.Magnetometer_RealSensor.y);
    z.push_back(SensorsData.Magnetometer_RealSensor.z);


    graphView_.graph(0)->setData(t, x);
    graphView_.graph(1)->setData(t, y);
    graphView_.graph(2)->setData(t, z);
    graphView_.replot();

    // A 25 elemmel ezelőtti infókat dobja el:
    if(x.size()>25){x.erase (x.begin(),x.begin()+1);}
    if(y.size()>25){y.erase (y.begin(),y.begin()+1);}
    if(z.size()>25){z.erase (z.begin(),z.begin()+1);}
}

void DisplayManager::on_Gyro3DButton_clicked()
{
    ActivateDisplay(DisplayManager::Graph);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Konténer kiürítése:
    intiGraph();// Arra az esetre, ha más szenzorról váltanánk erre a szenzorra.


    // Megjelnítési paraméterek átalakítása gyorsulási adatokhoz
    // give the axes some labels:
    graphView_.xAxis->setLabel("t[ms]");
    graphView_.yAxis->setLabel("Gyro");
    // set axes ranges, so we see all data:
    graphView_.xAxis->setRange(0, 25);
    graphView_.yAxis->setRange(-180, 180);
    graphView_.replot();

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlotG(const SensorsDataFormat&)));

    graphView_.graph(0)->setName("X Axis");
    graphView_.graph(1)->setName("Y Axis");
    graphView_.graph(2)->setName("Z Axis");
}

void DisplayManager::PipeInSlotG(const SensorsDataFormat& SensorsData)
{
    // Ha másodpercenként 5 adat érkezik és 5mpes időintervallumban kell ábrázolni
    // Az 25 pontot jelent.
    //qDebug() << SensorsData.Accelerometer_RealSensor.x;


    // Csak egy elemet hozzá kell adni push-al és az elsőt törölne earsel:
    // http://www.cplusplus.com/reference/stl/vector/erase/

    x.push_back(SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisX);
    y.push_back(SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisY);
    z.push_back(SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisZ);


    graphView_.graph(0)->setData(t, x);
    graphView_.graph(1)->setData(t, y);
    graphView_.graph(2)->setData(t, z);
    graphView_.replot();

    // A 25 elemmel ezelőtti infókat dobja el:
    if(x.size()>25){x.erase (x.begin(),x.begin()+1);}
    if(y.size()>25){y.erase (y.begin(),y.begin()+1);}
    if(z.size()>25){z.erase (z.begin(),z.begin()+1);}

}

void DisplayManager::on_LightButton_clicked()
{
    ActivateDisplay(DisplayManager::Graph);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Konténer kiürítése:
    intiGraph();// Arra az esetre, ha más szenzorról váltanánk erre a szenzorra.


    // Megjelnítési paraméterek átalakítása gyorsulási adatokhoz
    // give the axes some labels:
    graphView_.xAxis->setLabel("t[ms]");
    graphView_.yAxis->setLabel("Ambient Light");
    // set axes ranges, so we see all data:
    graphView_.xAxis->setRange(0, 25);
    graphView_.yAxis->setRange(0, 6);
    graphView_.replot();

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlotAL(const SensorsDataFormat&)));

    graphView_.graph(0)->setName("Ambient Light Sensor");
    graphView_.graph(1)->setName(" ");
    graphView_.graph(2)->setName(" ");
}

void DisplayManager::PipeInSlotAL(const SensorsDataFormat& SensorsData)
{
    x.push_back(SensorsData.Ambientlightsensor_RealSensor.LightLevel);

    graphView_.graph(0)->setData(t, x);
    graphView_.graph(1)->setData(t, y);
    graphView_.graph(2)->setData(t, z);
    graphView_.replot();

    if(x.size()>25){x.erase (x.begin(),x.begin()+1);}
}

void DisplayManager::on_ProxButton_clicked()
{
    ActivateDisplay(DisplayManager::Graph);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Konténer kiürítése:
    intiGraph();// Arra az esetre, ha más szenzorról váltanánk erre a szenzorra.


    // Megjelnítési paraméterek átalakítása gyorsulási adatokhoz
    // give the axes some labels:
    graphView_.xAxis->setLabel("t[ms]");
    graphView_.yAxis->setLabel("Proximity");
    // set axes ranges, so we see all data:
    graphView_.xAxis->setRange(0, 25);
    graphView_.yAxis->setRange(0, 2);
    graphView_.replot();

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlotP(const SensorsDataFormat&)));

    graphView_.graph(0)->setName("Proximity Sensor");
    graphView_.graph(1)->setName(" ");
    graphView_.graph(2)->setName(" ");

}

void DisplayManager::PipeInSlotP(const SensorsDataFormat& SensorsData)
{
    x.push_back(SensorsData.Proximitysensor_RealSensor.IsClose);

    graphView_.graph(0)->setData(t, x);
    graphView_.graph(1)->setData(t, y);
    graphView_.graph(2)->setData(t, z);
    graphView_.replot();

    if(x.size()>25){x.erase (x.begin(),x.begin()+1);}
}

void DisplayManager::on_cubeButton_clicked()
{
    ActivateDisplay(DisplayManager::OpenGL);

    //cubeView_.resize(800,600);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlotC(const SensorsDataFormat&)));
}

void DisplayManager::PipeInSlotC(const SensorsDataFormat &SensorsData)
{
    //Kocka orientációjának beállítása
    // Lehet, hogy a jó sorrend: ZYX de ZXY is lehet
    cubeView_.changeOrientation((float)SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisZ,(float)SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisY,(float)SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisX);

}

void DisplayManager::on_VelocityButton_clicked()
{
    //TODO
}

void DisplayManager::PipeInSlotS(const SensorsDataFormat& SensorsData)
{
    //TODO
}

void DisplayManager::on_Poz3DButton_clicked()
{
    ActivateDisplay(DisplayManager::Graph);

    //Szenzorkezelő modul leválasztása minden más modulról:
    disconnect(&TcpServer_, 0, 0, 0);

    // Konténer kiürítése:
    intiGraph();// Arra az esetre, ha más szenzorról váltanánk erre a szenzorra.


    // Megjelnítési paraméterek átalakítása gyorsulási adatokhoz
    // give the axes some labels:
    graphView_.xAxis->setLabel("Észak");
    graphView_.yAxis->setLabel("Kelet");
    // set axes ranges, so we see all data:
    graphView_.xAxis->setRange(0, 25);
    graphView_.yAxis->setRange(-180, 180);
    graphView_.replot();

    // Megfelelő feldolgozás kiválasztása a megjelenítendő infóhoz:
    connect(&TcpServer_,SIGNAL(PipeOutSignal(const SensorsDataFormat&)),this,SLOT(PipeInSlot3D(const SensorsDataFormat&)));

    graphView_.graph(0)->setName("Irány vektor");

    t.clear();
    x.clear();
    y.clear();
    z.clear();
}

void DisplayManager::PipeInSlot3D(const SensorsDataFormat& SensorsData)
{

    x.push_back(SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisX);
    y.push_back(SensorsData.Rotationvector_VirtualSensor.Degree_RotationAroundAxisY);


    graphView_.graph(0)->setData(x, y);
    //graphView_.graph(1)->setData(t, y);
    //graphView_.graph(2)->setData(t, z);
    graphView_.replot();

}


void DisplayManager::on_cameraButton_clicked()
{
    ActivateDisplay(DisplayManager::Camera);
}


void DisplayManager::intiGraph()
{//Kinulláza a vektorokat

    // Ha már voltak bennük adatok, dobják el őket
    x.erase(x.begin(),x.end());
    y.erase(y.begin(),y.end());
    z.erase(z.begin(),z.end());
    t.erase(t.begin(),t.end());

    int i=0;

    for (i=0; i<25; i++){
        x.push_back(0);
        y.push_back(0);
        z.push_back(0);
        t.push_back(i);
    }

}


void DisplayManager::cameraSettings(QString IP, QString Port, int FPS)
{
    cameraView_.ChangeSettings(IP,Port,FPS);
}



void DisplayManager::on_mainLinkButton_clicked()
{
    GoBackToMainMenu();
}

void DisplayManager::on_commandLinkButton_clicked()
{
    exitProgram();
}


