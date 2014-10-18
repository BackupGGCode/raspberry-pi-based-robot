#ifndef CONTROLLPANEL_H
#define CONTROLLPANEL_H

#include <QMainWindow>
#include "Displays/displaymanager.h"
#include "RemoteControll/AutoPilot/autopilot.h"
#include "RemoteControll/ManualControll/manualcontroll.h"

namespace Ui {
    class ControllPanel;
}

class ControllPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControllPanel(QWidget *parent = 0);
    ~ControllPanel();

private slots:
    void on_startButton_clicked();

    void on_connectButton_clicked();

    void on_cameraButton_clicked();

    void on_rpiButton_clicked();

    void ReturnToMainMenu();

    void exitProgram();

private:
    Ui::ControllPanel *ui;
    DisplayManager Display_;
    AutoPilot autoControll_;
    ManualControll manualControll_;

};

#endif // CONTROLLPANEL_H
