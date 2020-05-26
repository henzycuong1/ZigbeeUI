#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QStandardItem>
#include <QDebug>
#include <QProcess>
#include <QTextStream>
#include <QDir>
#include <stdio.h>
#include <QMessageBox>
#include "actions_engine.h"
#include "commissioning_engine.h"
#include "group_scene_engine.h"
#include "types.h"
using namespace std;

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT


public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

signals:

    void showUIConnection();

public slots:

    void newItem(unsigned int id, unsigned int address);

    void newItem(QStandardItem *item, unsigned int address);

    bool newDevice(unsigned int address);

    void receiveNetwork(QVariant ds_network);

    void receiveDevie(QVariant ds_device);

    void print_log(char *format);

private slots:

    void on_actionQuit_triggered();

    void on_actionConnect_triggered();

    void customContextMenu(QPoint pos);

    void processBind();

    void processAddGroup(uint8_t id);

    void processAddScene(uint8_t id);

    void processRemoveGroup();

    void processRemoveScene();

private:

    Ui::MainWindow *ui;

    void initModelView();

    void initConnect();

    void initAction();

    void initPropertyView();

    void selectItem(const QModelIndex &current, const QModelIndex &previous);

    void dataChange(QStandardItem *item);

    QStandardItemModel *modelItem = new QStandardItemModel;

    QStandardItemModel *modelProperty = new QStandardItemModel;

    QModelIndex currentIndex;

    QAction *rightBind;

    QMenu *rightGroup;

    QMenu *rightSceneStore;

    QAction *rightSceneRecall;

    QAction *rightGroup_0,*rightGroup_1,*rightGroup_2,*rightGroup_3,*rightGroup_4,*rightGroup_5,*rightGroup_6,*rightGroup_7,*rightGroup_8,*rightGroup_9;

    QAction *rightScene_0,*rightScene_1, *rightScene_2, *rightScene_3, *rightScene_4, *rightScene_5, *rightScene_6, *rightScene_7, *rightScene_8, *rightScene_9;

    QAction *rightRemoveGroup,*rightRemoveScene;

    QString string = "";

};
#endif // MAINWINDOW_H
