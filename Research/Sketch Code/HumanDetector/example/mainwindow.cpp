#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this,SIGNAL(startC()),this,SLOT(startClient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{     
    startC();
}

void MainWindow::startClient()
{
    cv::VideoCapture vcap;
    cv::Mat raw_image;

    if(!vcap.open(0))
    {
        qDebug() << "Error opening video stream";
        return;
    }
    else
    {
        qDebug() << "Stream opened";
    }

    cv::CascadeClassifier cascade;

    if(!cascade.load("d://3rdParty/haarcascade_frontalface_alt.xml"))
    {
        qDebug() << "Error opening detector";
        return;
    }
    else
    {
        qDebug() << "Detector loaded";
    }



    cv::namedWindow("Cam", CV_WINDOW_NORMAL);
    cv::setWindowProperty("Cam", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);


    while(true)
    {
        vcap >> raw_image;

        std::vector<cv::Rect> bodies;
        cascade.detectMultiScale(raw_image, bodies, 1.1, 3, 0 | CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
        if (bodies.empty() == false)
        {
            //mean_point = (bodies[0].tl() + bodies[0].br()) * 0.5;
            cv::rectangle(raw_image,bodies[0],cv::Scalar(0,255,0),2,8);
        }


        cv::imshow("Cam",raw_image);

        if (cv::waitKey(30) >= 0) break;
    }

    cv::destroyWindow("Cam");
}
