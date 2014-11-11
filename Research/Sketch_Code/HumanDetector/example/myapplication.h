#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

/*
http://qt-project.org/doc/qt-5/exceptionsafety.html
GUI alkalmazásoknál nem biztonságos a try catch:
http://qt-project.org/doc/qt-5/exceptionsafety.html
 It is not safe to call a GUI related function after catching an exception.

A QDebugon keresztül egy expection kifejezést tartalmazó stringet el lehet kapni
A Logger-ből még azt is le lehet kérdezni, hogy melyik fv. küldte, melyik sor.
Az interrupt szignált ekkor meglehet hívni.
--------------------------------------------------
http://stackoverflow.com/questions/4661883/qt-c-error-handling
http://stackoverflow.com/questions/15293105/why-cant-i-use-qmessagebox-in-qapplicationnotify-derived-method
http://comments.gmane.org/gmane.comp.lib.qt.general/33711
Fontos: http://stackoverflow.com/questions/8247404/why-does-this-simple-qt-application-not-link
*/

#include <QObject>
#include <QApplication>
#include "myerrorhandler.h"
#include "mainwindow.h"

class MyApplication : public QApplication
{
    Q_OBJECT

public:
    explicit MyApplication(int &argc, char **argv);
    ~MyApplication();

    // override to handle out of memory exceptions
    bool notify( QObject* receiver, QEvent* e );

private:
    MainWindow window_;
};

#endif // MYAPPLICATION_H
