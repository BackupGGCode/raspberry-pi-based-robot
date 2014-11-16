#ifndef OBJECTEXTRACTION_H
#define OBJECTEXTRACTION_H

#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QThread>
#include <typeinfo>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "myerrorhandler.h"

class ObjectExtraction : public QThread
{
    Q_OBJECT
public:
    explicit ObjectExtraction(QObject *parent = 0);
    ~ObjectExtraction();

    void Init(QString detectorXML, int cameraID);

    void run();

    void Stop();
   // bool IsActive();//Már vanak ilyenen néven fv.-ek a QThread-ben.
   // bool Pause();
   // bool Continue();

signals:
    void SendFrame(QImage image);

private:
    void Search();
    void drawRects(cv::Mat &img, std::vector<cv::Rect> &objects);

    bool stopRecived_;
    cv::VideoCapture vcap_;
    cv::CascadeClassifier cascade_;

    cv::Scalar lineColor;
};

#endif // OBJECTEXTRACTION_H
