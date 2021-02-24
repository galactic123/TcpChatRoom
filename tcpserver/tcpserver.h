#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui { class tcpserver; }
QT_END_NAMESPACE

class tcpserver : public QMainWindow
{
    Q_OBJECT

public:
    tcpserver(QWidget *parent = nullptr);
    ~tcpserver();

private slots:
    void on_btn_connect_clicked();
    void doprocessOnConnect();
    void doprocessOnConnectError(QAbstractSocket::SocketError);
    void doprocessOnDisconnect();
    void doprocessOnReadyRead();
    void on_btn_send_clicked();
    void doprocessOnConnected();

private:
    Ui::tcpserver *ui;
    QTcpServer* myserver;
    QList<QTcpSocket*>clients;
    void init();

};
#endif // TCPSERVER_H
