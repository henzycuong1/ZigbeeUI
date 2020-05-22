#include "mainwindow.h"
#include "data_structures.h"
#include "uiconnection.h"
#include "zigbee.h"
#include <QApplication>
#include <QThread>
#include <stdio.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
    qRegisterMetaType<std::string>();
    QApplication a(argc,argv);
    QThread *thread_zigbee = new QThread;

    zigbee *z = new zigbee;

    z->moveToThread(thread_zigbee);

    QObject::connect(&a,&QApplication::aboutToQuit,thread_zigbee,&QThread::quit);

    MainWindow *w = new MainWindow;
    uiconnection *option = new uiconnection;

    QObject::connect(w,&MainWindow::showUIConnection,option,&uiconnection::show);

    QObject::connect(z,&zigbee::hasBeenConnected,w,&MainWindow::receiveNetwork);
    QObject::connect(z,&zigbee::hasBeenConnected,option,&uiconnection::receiveNetwork);

    QObject::connect(z,&zigbee::newDevice,w,&MainWindow::receiveDevie);

    QObject::connect(option,&uiconnection::startConnect,z,&zigbee::init);

    thread_zigbee->start();
    w->show();

    int result = a.exec();
    return  result;

}
