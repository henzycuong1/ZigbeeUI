#ifndef UICONNECTION_H
#define UICONNECTION_H

#include <QWidget>
#include <QRegExpValidator>
#include <QDebug>
#include <stdio.h>
#include "types.h"

using namespace std;

namespace Ui {
class uiconnection;
}

class uiconnection : public QWidget

{
    Q_OBJECT

public:

    explicit uiconnection(QWidget *parent = nullptr);

    ~uiconnection();

public slots:

    void receiveNetwork(QVariant ds_network);

signals:

    void startConnect(string argv_1,unsigned int argv_2,string argv_3,unsigned int argv_4,string argv_5,unsigned int argv_6);

private slots:

    void on_buttonConnect_clicked();

    void on_buttonCancel_clicked();

private:

    void initInput();

    Ui::uiconnection *ui;

};

#endif // UICONNECTION_H
