#include "tcpclient.h"
#include "ui_tcpclient.h"

Tcpclient::Tcpclient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tcpclient)
{
    ui->setupUi(this);
    init();
}

Tcpclient::~Tcpclient()
{
    delete ui;
}
void Tcpclient::init()
{
    myclient = new QTcpSocket(this);
}

void Tcpclient::on_btn_connect_clicked()
{
    QString serverIP = ui->server_ip->text();
    QString serverPort = ui->server_port->text();
    myclient->connectToHost(QHostAddress(serverIP),serverPort.toUInt());
    connect(myclient,SIGNAL(connected()),this,SLOT(doProcessConnected()));
    connect(myclient,SIGNAL(readyRead()),this,SLOT(doProcessReadyRead()));
    connect(myclient,SIGNAL(disconnected()),this,SLOT(doProcessDisConnected()));
    connect(myclient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(doProcessError(QAbstractSocket::SocketError)));
}
void Tcpclient::doProcessConnected()
{
    ui->textEdit->append("连接成功");
}
void Tcpclient::doProcessReadyRead()
{

    QString str;
    while (!myclient->atEnd()) {
        QString pro = QString("客户端[%1:%2]发送：").arg(myclient->peerAddress().toString()).arg(myclient->peerPort());
        str = QString(pro+myclient->readAll());


    }
     ui->textEdit->append(str);
}
void Tcpclient::doProcessDisConnected()
{
    ui->textEdit->append("服务器断开");
}
void Tcpclient::doProcessError(QAbstractSocket::SocketError err)
{
    qDebug() << err;
}

void Tcpclient::on_btn_send_clicked()
{
    QString msg = ui->textEdit_2->toPlainText();
    int ret = myclient->write(msg.toUtf8());
    if(ret <= 0)return;
    ui->textEdit_2->clear();
}
