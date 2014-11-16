#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objectextraction.h"


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
    void ReciveFrame(QImage image);

private:
    void drawRects(cv::Mat& img, std::vector<cv::Rect>& objects);

    Ui::MainWindow *ui;
    ObjectExtraction *extractor;
};

#endif // MAINWINDOW_H
