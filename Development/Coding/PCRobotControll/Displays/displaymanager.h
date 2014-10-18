#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <QWidget>
#include <Displays/cameradisplay.h>
#include <Displays/myglwidget.h>
#include <Displays/qcustomplot.h>
#include <Communication/TcpServer.h>
#include <SensorData/sensorsdataformat.h>

namespace Ui {
    class DisplayManager;
}

class DisplayManager : public QWidget
{
    Q_OBJECT

public:

    enum DisplayType{
        Camera = 0,
        Graph,
        OpenGL
    };

    explicit DisplayManager(QWidget *parent = 0);
    ~DisplayManager();
    void ActivateDisplay(DisplayType Selected);
    bool IsConnected();
    bool cameraIsConnected();

private:
    Ui::DisplayManager *ui;
    MyGLWidget cubeView_;
    CameraDisplay cameraView_;
    QCustomPlot graphView_;

    TcpServer TcpServer_;
    bool connectionState_;
    QVector<double> x,y,z,t;

    void intiGraph();

public slots:
    void connectionSucces();

    void PipeInSlotA(const SensorsDataFormat&  SensorsData);
    void PipeInSlotL(const SensorsDataFormat&  SensorsData);
    void PipeInSlotM(const SensorsDataFormat&  SensorsData);
    void PipeInSlotG(const SensorsDataFormat&  SensorsData);
    void PipeInSlotAL(const SensorsDataFormat&  SensorsData);
    void PipeInSlotP(const SensorsDataFormat&  SensorsData);
    void PipeInSlotC(const SensorsDataFormat&  SensorsData);
    void PipeInSlotS(const SensorsDataFormat&  SensorsData);
    void PipeInSlot3D(const SensorsDataFormat&  SensorsData);

    void on_AccelButton_clicked();
    void on_LinearButton_clicked();
    void on_MagButton_clicked();
    void on_LightButton_clicked();
    void on_ProxButton_clicked();
    void on_Gyro3DButton_clicked();
    void on_cubeButton_clicked();
    void on_cameraButton_clicked();
    void on_VelocityButton_clicked();
    void on_Poz3DButton_clicked();

    void cameraSettings(QString IP,QString Port, int FPS);

private slots:
    void on_mainLinkButton_clicked();

    void on_commandLinkButton_clicked();

signals:
    void GoBackToMainMenu();
    void exitProgram();
};

#endif // DISPLAYMANAGER_H
