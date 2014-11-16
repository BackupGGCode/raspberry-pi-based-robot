#include "objectextraction.h"

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

ObjectExtraction::ObjectExtraction(QObject *parent) :
    QThread(parent)
{
    stopRecived_ = false;
    lineColor = cv::Scalar(0,255,255);
}

ObjectExtraction::~ObjectExtraction()
{

}

void ObjectExtraction::Init(QString detectorXML, int cameraID)
{
    if(!vcap_.open(cameraID))
    {
        throw_line("Error opening video stream");
    }
    else
    {
        qDebug() << "Stream opened";
    }

    //"d://3rdParty/haarcascade_frontalface_alt.xml"
    if(!cascade_.load(detectorXML.toStdString()))
    {
        throw_line("Error opening detector");
    }
    else
    {
        qDebug() << "Detector loaded";
    }
}

void ObjectExtraction::run()
{
    try
    {
        this->Search();
    }
    catch (std::exception &e)
    {
        qCritical("Error %s", e.what());
    }
    catch (...)
    {
        qCritical("Error <unknown> in thread");
    }
}

void ObjectExtraction::Stop()
{
    stopRecived_ = true;
    QThread::msleep(500);
    return;
}

void ObjectExtraction::Search()
{
    while(!stopRecived_)
    {
        cv::Mat raw_image;
        vcap_ >> raw_image;

        std::vector<cv::Rect> objects;
        cascade_.detectMultiScale(raw_image, objects, 1.1,
                                 3, 0 | CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
                                 cv::Size(30, 30));

        drawRects(raw_image,objects);

        SendFrame(Mat2QImage(raw_image));


        QThread::msleep(50);//20fps
    }

    stopRecived_ = false;
}

void ObjectExtraction::drawRects(cv::Mat &img, std::vector<cv::Rect> &objects)
{
    if (objects.empty() == false)
    {
       //mean_point = (bodies[0].tl() + bodies[0].br()) * 0.5;

        int biggestRectIndex = 0;
        for(int i = 0; i < (int)objects.size(); i++)
        {
          if(objects[i].area() > objects[biggestRectIndex].area())
          {
              biggestRectIndex = i;
          }
        }

        for(int i = 0; i < (int)objects.size(); i++)
        {
            if(i != biggestRectIndex)
            {
                cv::rectangle(img,objects[i],cv::Scalar(0,255,0),2,8);
            }
        }

        //cv::rectangle(img,bodies[biggestRectIndex],cv::Scalar(0,255,0),2,8);

        cv::Point center( objects[biggestRectIndex].x + objects[biggestRectIndex].width*0.5,
                 objects[biggestRectIndex].y + objects[biggestRectIndex].height*0.5 );

        cv::ellipse( img, center,
                      cv::Size( objects[biggestRectIndex].width*0.5, objects[biggestRectIndex].height*0.5),
                 0, 0, 360, lineColor, 4, 8, 0 );


        cv::Point up1(objects[biggestRectIndex].x + (objects[biggestRectIndex].width / 2),
                      objects[biggestRectIndex].y);
        cv::Point up2(objects[biggestRectIndex].x + (objects[biggestRectIndex].width / 2),
                      0);
        cv::line(img,up1,up2,lineColor,2,8);

        cv::Point down1(objects[biggestRectIndex].x + (objects[biggestRectIndex].width / 2),
                        objects[biggestRectIndex].y + objects[biggestRectIndex].height);
        cv::Point down2(objects[biggestRectIndex].x + (objects[biggestRectIndex].width / 2),
                        img.rows);
        cv::line(img,down1,down2,lineColor,2,8);

        cv::Point left1(objects[biggestRectIndex].x,
                        objects[biggestRectIndex].y + (objects[biggestRectIndex].height / 2));
        cv::Point left2(0,
                        objects[biggestRectIndex].y + (objects[biggestRectIndex].height / 2));
        cv::line(img,left1,left2,lineColor,2,8);

        cv::Point right1(objects[biggestRectIndex].x + objects[biggestRectIndex].width,
                         objects[biggestRectIndex].y + (objects[biggestRectIndex].height / 2));
        cv::Point right2(img.cols,
                         objects[biggestRectIndex].y + (objects[biggestRectIndex].height / 2));
        cv::line(img,right1,right2, lineColor,2,8);

    }
}
