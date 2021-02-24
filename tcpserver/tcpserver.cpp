#include "tcpserver.h"
#include "ui_tcpserver.h"

tcpserver::tcpserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tcpserver)
{
    ui->setupUi(this);
    init();
}

tcpserver::~tcpserver()
{
    delete ui;
}
void tcpserver::init()
{
    myserver = new QTcpServer(this);

}



void tcpserver::on_btn_connect_clicked()
{
    //自动配置ip
//    QList<QHostAddress>add = QNetworkInterface::allAddresses();
//    for (int i=0;i<add.length();i++) {
//        QHostAddress addr = add.at(i);
//        qDebug()<<addr.toString();
//    }
    //手动配置ip
    QString myadd = ui->clientAddress->text();
    QString myport = ui->clientPort->text();
    bool connectResult = myserver->listen(QHostAddress(myadd),myport.toInt());
    if(!connectResult)
    {
        ui->textEdit->append("连接失败");
    }
    else{
        ui->textEdit->append("连接成功");
    }

    myserver->setMaxPendingConnections(100);
    connect(myserver,SIGNAL(newConnection()),this,SLOT(doprocessOnConnect()));
    connect(myserver,SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this,SLOT(doprocessOnConnectError(QAbstractSocket::SocketError)));
}
void tcpserver::doprocessOnConnect(){
    QTcpSocket *client = myserver->nextPendingConnection();//当前的连接者
    clients.append(client);
    connect(client,SIGNAL(disconnected()),this,SLOT(doprocessOnDisconnect()));//客户端退出
    connect(client,SIGNAL(readyRead()),this,SLOT(doprocessOnReadyRead()));//读取客户端内容
    connect(client,SIGNAL(connected()),this,SLOT(doprocessOnConnected()));
}
void tcpserver::doprocessOnConnectError(QAbstractSocket::SocketError err)
{
    qDebug()<<err;
}
void tcpserver::doprocessOnDisconnect()
{
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QString msg = QString("客户端[%1:%2] 退出！")
            .arg(client->peerAddress().toString())//客户端地址和端口
            .arg(client->peerPort()) ;
    ui->textEdit->append(msg);
    for (int i=0;i<clients.length();i++) {//删除对应的client
        if(clients.at(i)->peerAddress().toString() == client->peerAddress().toString()
                &&clients.at(i)->peerPort() == client->peerPort())
        {
            clients.removeAt(i);
            break;
        }
    }
}
void tcpserver::doprocessOnReadyRead()//读取客户端发送的东西
{
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QString str;
    while (!client->atEnd()) {
        QString pro = QString("客户端[%1:%2]发送：").arg(client->peerAddress().toString()).arg(client->peerPort());
        str = QString(pro+client->readAll());


    }
     ui->textEdit->append(str);
}
void tcpserver::doprocessOnConnected()
{
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QString msg = QString("客户端[%1:%2]连入")
            .arg(client->peerAddress().toString())//客户端地址和端口
            .arg(client->peerPort());
    ui->textEdit->append(msg);
}
void tcpserver::on_btn_send_clicked()
{
    QString ip = ui->client_ip->text();
    quint16 port = ui->client_port->text().toUInt();

    for(int i=0;i<clients.length();i++)
    {

        if(clients.at(i)->peerAddress().toString() == ip
                &&clients.at(i)->peerPort() == port)
        {
            QString msg = ui->sendmessage->toPlainText();
            qDebug()<<msg;
            clients.at(i)->write(msg.toUtf8());

            break;
        }
    }
}
