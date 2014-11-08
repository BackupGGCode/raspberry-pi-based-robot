#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

//http://stackoverflow.com/questions/17127762/cvmat-to-qimage-and-back
QImage Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

cv::Mat QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true);

    connect(&timer_,SIGNAL(timeout()),this,SLOT(getFrame()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{     

    if(!vcap.isOpened())
    {
        if(!vcap.open(0))
        {
            qDebug() << "Error opening video stream";
            return;
        }
        else
        {
            qDebug() << "Stream opened";
        }
    }

    if(timer_.isActive())
    {
        timer_.stop();
    }
    else
    {
        timer_.start(50);//20Fps
    }


    /*
     *Működik
     * QImage image("C:/Users/user/Pictures/a7Kw1jw_700b_v1.jpg");
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));*/

    /*
     *Működik
     * cv::Mat image = cv::imread("C:/Users/user/Pictures/a7Kw1jw_700b_v1.jpg");
    ui->imageLabel->setPixmap(QPixmap::fromImage(Mat2QImage(image)));*/
}

void MainWindow::getFrame()
{
    cv::Mat raw_image;
    vcap >> raw_image;
    ui->imageLabel->setPixmap(QPixmap::fromImage(Mat2QImage(raw_image)));

}
