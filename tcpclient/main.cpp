#include "tcpclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tcpclient w;
    w.show();
    return a.exec();
}
