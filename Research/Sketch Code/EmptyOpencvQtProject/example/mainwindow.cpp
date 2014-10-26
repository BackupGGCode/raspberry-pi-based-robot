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

    /*
    cv::Mat image;
    image = cv::imread("C:/Users/user/Pictures/a7Kw1jw_700b_v1.jpg");
    qDebug() << image.cols;
    qDebug() << image.rows;

    cv::imshow("Display window", image);
    cv::waitKey(10);
    */

    cv::VideoCapture vcap;
    cv::Mat raw_image;

    const std::string videoStreamAddress =
            "http://192.168.2.100:8080/video.mjpg";

    if(!vcap.open(videoStreamAddress))
    {
        qDebug() << "Error opening video stream";
        return;
    }

    qDebug() << "Stream opened";

    while(true)
    {
        vcap >> raw_image;
        cv::imshow("Cam",raw_image);

        if (cv::waitKey(30) >= 0) break;
    }
}
