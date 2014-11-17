#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

/*
- Követés - gyorsítás
 https://gist.github.com/yoggy/1451097
- Többszálúsítás - mint az AlgorithmTesternél.
- Hibakezelés - Mint az AlgorithmTesternél.
- Qt - GUI
- Jobb arc detektor
- Arc kivágása kis ablakba
- Animált rect
- Kálmán szűrővel a rect 2d koordinátáinak és méretének követése

*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true);

    this->extractor = NULL;

    this->show();

}

MainWindow::~MainWindow()
{
    if(extractor != NULL)
    {
        if(extractor->isRunning())
        {
            extractor->Stop();
        }
        delete extractor;
    }

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{     
    QString detectorXML("d://3rdParty/haarcascade_frontalface_alt.xml");
    int cameraID = 0;

    if(extractor == NULL)
    {
        extractor = new ObjectExtraction();

        connect(extractor,SIGNAL(SendFrame(QImage)), this, SLOT(ReciveFrame(QImage)));

        extractor->Init(detectorXML, cameraID);
        extractor->start();
    }
    else
    {
        if(extractor->isPaused())
        {
            extractor->Resume();
        }
        else
        {
            extractor->Pause();
        }
    }
}

void MainWindow::ReciveFrame(QImage image)
{
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}


