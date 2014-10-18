#ifndef MANUALCONTROLL_H
#define MANUALCONTROLL_H

#include <QWidget>
#include <QKeyEvent>
#include "Communication/TcpClient.h"

namespace Ui {
    class ManualControll;
}

class ManualControll : public QWidget
{
    Q_OBJECT

public:
    explicit ManualControll(QWidget *parent = 0);
    ~ManualControll();
    void ChangeSettings(QString IP, QString Port);
    bool IsConnected();

private:
    Ui::ManualControll *ui;
    TcpClient connectionOverTCP_;
    QString Message_;
    QTimer keyTimer_;

private slots:
   void GetRobotAnswers(QString answer);
   void on_forward_clicked();
   void on_forward_pressed();
   void on_left_clicked();
   void on_left_pressed();
   void on_right_clicked();
   void on_right_pressed();
   void on_backward_clicked();
   void on_backward_pressed();
   void on_dial_sliderReleased();
   void on_dial_PWM_sliderReleased();
   void send_stop();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool isPressed_;
    bool isReleased_;
    Qt::Key key_;
    Qt::Key prevSet_;

private slots:
    void KeyFilter();//Prellegés mentesítés
    void on_resetButton_clicked();
    void on_offButton_clicked();
    void on_quitButton_clicked();
};

#endif // MANUALCONTROLL_H
