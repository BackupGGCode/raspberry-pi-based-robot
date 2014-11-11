#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "myerrorhandler.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void getFrame();

private:
    void drawRects(cv::Mat& img, std::vector<cv::Rect>& objects);

    Ui::MainWindow *ui;
    QTimer timer_;
    cv::VideoCapture vcap;
    cv::CascadeClassifier cascade;
    cv::Scalar lineColor;
};

#endif // MAINWINDOW_H
