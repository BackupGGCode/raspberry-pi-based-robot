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
        //Kellene egy frame manager, ami csak frameket rögzít (esetleg előfeldolgozást végez - szürke skálázás)
        //Ezt a framemanagert kellene összekapcsolni egy szignállal a detektálással, követéssel és megjelenítéssel
        //Illetve külön a detektálás -> (Template) -> Követés -> (Rect) -> Megjelenítés összekapcsolása
        //A megjelenítés már csak rá rajzolja a framemanager-től kapott frame-re a követéstől kapott rectet.
		
		//Jó ötletnek tűnik:
		//A template-et követés közben is lehet frissíteni a templatet, a korábbi template alapján megtalált helyen látott minta alapján. 
		
		//Egyéb template maching használathoz:
		//https://gist.github.com/yoggy/1451097
		//http://stackoverflow.com/revisions/20180073/3
		//http://docs.opencv.org/modules/imgproc/doc/object_detection.html
		//http://opencv-code.com/tutorials/fast-template-matching-with-image-pyramid/
		//http://samwize.com/2013/06/09/using-opencv-to-match-template-multiple-times/
		//http://stackoverflow.com/questions/20180073/real-time-template-matching-opencv-c
		//http://docs.opencv.org/trunk/doc/py_tutorials/py_imgproc/py_template_matching/py_template_matching.html

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


