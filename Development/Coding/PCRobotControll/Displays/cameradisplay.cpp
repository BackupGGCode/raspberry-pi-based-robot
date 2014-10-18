#include "cameradisplay.h"
#include "ui_cameradisplay.h"
#include <QDebug>

CameraDisplay::CameraDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CameraDisplay)
{
    connect(&timer_,SIGNAL(timeout()),this,SLOT(refreshImage()));
    connect(&netWorkManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(netWorkManagerFinished(QNetworkReply*)));

    ui->setupUi(this);

    frameCounter_ = 1;

    FPS_ = 1;

    connectionState_ = false;
}

CameraDisplay::~CameraDisplay()
{
    delete ui;
}

void CameraDisplay::netWorkManagerFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        reply->deleteLater();
        return;
    }
    QVariant redir = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (redir.isValid()) {
        QUrl url = redir.toUrl();
        qDebug() << "must go to:" << url;
        if (url.isRelative()) {
            qDebug() << "Is relative setting scheme and host";
            url.setScheme(reply->url().scheme());
            url.setEncodedHost(reply->url().encodedHost());
        }
        QNetworkRequest req(url);
        netWorkManager_.get(req);
        reply->deleteLater();
        return;
    }
    qDebug() << "ContentType:" << reply->header(QNetworkRequest::ContentTypeHeader).toString();

    QByteArray jpegData = reply->readAll();

    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    ui->ImageOfCamera->setPixmap(pixmap);
    ui->statusBar->showMessage(QString("%1").arg(reply->url().toString()));
    reply->deleteLater();

    //Ha idáig eljut
    connectionState_ = true;
}

void CameraDisplay::refreshImage()
{

    //QUrl url("http://192.168.43.1:8080/shot.jpg?1");
    QUrl url("http://" + IP_ + ":" + Port_ + "/shot.jpg?" + QString::number(frameCounter_));
    //QUrl url(ui->m_cbAddress->currentText());

    if(frameCounter_ == FPS_)
    {
        frameCounter_ = 1;
    }else{
        frameCounter_++;
    }

    if ( ! url.isValid()) {
        qDebug() << "Invalid url" << url;
        return;
    }
    qDebug() << "Starting to download" << url;
    QNetworkRequest request(url);
    /*
     [HTTP_USER_AGENT] => Opera/9.80 (X11; Linux x86_64; U; lt) Presto/2.6.31 Version/10.70
     [HTTP_HOST] => vvv.laisvas.lt [HTTP_ACCEPT] => text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, * / *;q=0.1
     [HTTP_ACCEPT_LANGUAGE] => lt-LT,lt;q=0.CameraDisplay9,en;q=0.8
     [HTTP_ACCEPT_CHARSET] => iso-8859-1, utf-8, utf-16, *;q=0.1
     [HTTP_ACCEPT_ENCODING] => deflate, gzip, x-gzip, identity, *;q=0
     [HTTP_CACHE_CONTROL] => no-cache
     [HTTP_CONNECTION] => Keep-Alive, TE
     [HTTP_TE] => deflate, gzip, chunked, identity, trailers
    */
    // imitate opera browser.
    request.setRawHeader("User-Agent", "Opera/9.80 (X11; Linux x86_64; U; en) Presto/2.6.31 Version/10.70");
    request.setRawHeader("Accept", "text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1");
    request.setRawHeader("Accept-Language", "lt-LT,lt;q=0.9,en;q=0.8");
    request.setRawHeader("Accept-Charset", "iso-8859-1, utf-8, utf-16, *;q=0.1");
    request.setRawHeader("Accept-Encoding","deflate, gzip, x-gzip, identity, *;q=0");

    netWorkManager_.get(request);
}


void CameraDisplay::ChangeSettings(QString IP, QString Port, int FPS)
{

    if(timer_.isActive() == true)
    {
        timer_.stop();
    }

    IP_.clear();
    Port_.clear();

    FPS_ = FPS;
    IP_ = IP;
    Port_ = Port;

    timer_.start(1000/FPS_);
}

bool CameraDisplay::IsConnected()
{
    return connectionState_;
}

void CameraDisplay::Stop()
{
    timer_.stop();
}

void CameraDisplay::Start()
{
    timer_.start(1000/FPS_);
}
