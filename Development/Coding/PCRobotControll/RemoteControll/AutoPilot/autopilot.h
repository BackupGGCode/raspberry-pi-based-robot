#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include <QWidget>

namespace Ui {
    class AutoPilot;
}

class AutoPilot : public QWidget
{
    Q_OBJECT

public:
    explicit AutoPilot(QWidget *parent = 0);
    ~AutoPilot();

private:
    Ui::AutoPilot *ui;
};

#endif // AUTOPILOT_H
