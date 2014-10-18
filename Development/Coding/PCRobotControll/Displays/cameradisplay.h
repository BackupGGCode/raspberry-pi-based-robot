#ifndef CAMERADISPLAY_H
#define CAMERADISPLAY_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QNetworkRequest>

namespace Ui {
    class CameraDisplay;
}

class CameraDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraDisplay(QWidget *parent = 0);
    ~CameraDisplay();
    void ChangeSettings(QString IP,QString Port, int FPS);
    bool IsConnected();
    void Stop();
    void Start();

private:
    Ui::CameraDisplay *ui;
    QNetworkAccessManager netWorkManager_;
    QTimer timer_;
    QNetworkRequest request_;

    QString IP_;
    QString Port_;
    int FPS_;
    int frameCounter_;

    bool connectionState_;


private slots:
    void refreshImage();
    void netWorkManagerFinished(QNetworkReply *reply);
};

#endif // CAMERADISPLAY_H
