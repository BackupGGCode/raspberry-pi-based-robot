#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cv::Mat image;
    image = cv::imread("C:/Users/user/Pictures/a7Kw1jw_700b_v1.jpg");
    qDebug() << image.cols;
    qDebug() << image.rows;

    cv::imshow("Display window", image);
    cv::waitKey(10);
}
