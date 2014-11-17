#ifndef OBJECTEXTRACTION_H
#define OBJECTEXTRACTION_H

#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QThread>
#include <typeinfo>
#include <qwaitcondition.h>

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

    void Pause();

    void Resume();

    bool isPaused();

signals:
    void SendFrame(QImage image);

private:
    void Search();
    void drawRects(cv::Mat &img, std::vector<cv::Rect> &objects);

    QMutex sync;
    QWaitCondition pauseCond;
    bool pause_;

    bool stopRecived_;
    cv::VideoCapture vcap_;
    cv::CascadeClassifier cascade_;

    cv::Scalar lineColor;
};

#endif // OBJECTEXTRACTION_H
