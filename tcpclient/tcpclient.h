#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
QT_BEGIN_NAMESPACE
namespace Ui { class Tcpclient; }
QT_END_NAMESPACE

class Tcpclient : public QMainWindow
{
    Q_OBJECT

public:
    Tcpclient(QWidget *parent = nullptr);
    ~Tcpclient();

private slots:
    void on_btn_connect_clicked();
    void doProcessConnected();
    void doProcessReadyRead();
    void doProcessDisConnected();
    void doProcessError(QAbstractSocket::SocketError);

    void on_btn_send_clicked();

private:
    Ui::Tcpclient *ui;
    void init();
    QTcpSocket* myclient;
};
#endif // TCPCLIENT_H
