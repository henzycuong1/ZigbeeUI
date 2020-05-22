#include "mainwindow.h"
#include "ui_mainwindow.h"

#define COL_PROPERTY 0
#define COL_VALUE 1

#define ROLE_PARENT 1000
#define ROLE_ITEM 1001
#define ROLE_PROPERTY 1002
#define ROLE_IEEE_ADDR 1100
#define ROLE_ENDPOINT 1101
#define ROLE_GROUP_ADDR 1102
#define ROLE_DEVICE_I 1103
Q_DECLARE_METATYPE(network_info_t)
Q_DECLARE_METATYPE(device_info_t)

const QString listProperty[5] = {"ON_OFF","LVL","HUE","SAT","PERMIT_JOIN"};

zb_addr_t des;

uint8_t ui_selected_group = 0;

uint8_t ui_selected_scene = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initModelView();
    initAction();
    initConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newItem(unsigned int id, unsigned int address)
{
    auto parent = modelItem->findItems(QString(address));
    QStandardItem *item = new QStandardItem;
    item->setData(QString::number(id),Qt::DisplayRole);
    item->setData(QVariant(false),ROLE_PARENT);
    item->setData(QVariant(true),ROLE_ITEM);
    if(parent.count() > 0){
        parent.at(0)->appendRow(item);
    }else{
        modelItem->appendRow(item);
    }
}

void MainWindow::newItem(QStandardItem *item, unsigned int address)
{
    item->setData(QVariant(false),ROLE_PARENT);
    item->setData(QVariant(true),ROLE_ITEM);
    auto parent = modelItem->findItems(QString(address));
    if(parent.count() > 0){
        parent.at(0)->appendRow(item);
    }else{
        modelItem->appendRow(item);
    }
}

void MainWindow::newDevice(unsigned int address)
{
    QStandardItem *item = new QStandardItem;
    item->setData(QString::number(address),Qt::DisplayRole);
    item->setData(QVariant(true),ROLE_PARENT);
    item->setData(QVariant(false),ROLE_ITEM);
    modelItem->appendRow(item);
}

void MainWindow::receiveNetwork(QVariant ds_network)
{

    network_info_t ds_network_info = ds_network.value<network_info_t>();
    ui->labelConnect->setText("EXTPANID: " + QString::number(ds_network_info.ext_pan_id) +
                              " PANID: " + QString::number(ds_network_info.pan_id) +
                              " CHANNEL: " + ds_network_info.nwk_channel +
                              " STATE: " + ds_network_info.state);
}

void MainWindow::receiveDevie(QVariant ds_device, int i)
{
    device_info_t ds_device_info = ds_device.value<device_info_t>();
    auto parent = modelItem->findItems(QString(ds_device_info.nwk_addr));
    QStandardItem *item = new QStandardItem;
    item->setData(QVariant::fromValue(ds_device_info.ieee_addr),ROLE_IEEE_ADDR);
    item->setData(ds_device_info.ep_list[i].endpoint_id,ROLE_ENDPOINT);
    item->setData(0xFFFFFF,ROLE_GROUP_ADDR);
    item->setData(ds_device_info.ep_list->device_id,Qt::DisplayRole);
    item->setData(i,ROLE_DEVICE_I);
    if(parent.count() > 0){
        newItem(item,ds_device_info.nwk_addr);
    }else{
        newDevice(ds_device_info.nwk_addr);
        newItem(ds_device_info.ep_list->device_id,ds_device_info.nwk_addr);
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::initModelView()
{
    modelItem->setHorizontalHeaderLabels({tr("Devices")});
    modelProperty->setHorizontalHeaderLabels({tr("Property"),tr("Value")});
    modelItem->setColumnCount(1);
    modelProperty->setColumnCount(2);
    ui->viewItem->setModel(modelItem);
    ui->viewProperty->setModel(modelProperty);
    ui->viewItem->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::on_actionConnect_triggered()
{
    emit showUIConnection();
}

void MainWindow::customContextMenu(QPoint pos)
{
    QModelIndex index = ui->viewItem->indexAt(pos);
    currentIndex = index;
    if(index.data(ROLE_ITEM).toBool()){
        QMenu *menu = new QMenu(this);
        menu->addAction(rightBind);
        menu->addMenu(rightGroup);
        menu->addAction(rightRemoveGroup);
        menu->addMenu(rightSceneStore);
        menu->addAction(rightRemoveScene);
        menu->addAction(rightSceneRecall);
        menu->popup(ui->viewItem->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::processBind()
{
    QMessageBox::warning(this,"Furture's being constructed","Furture's being constructed");
}

void MainWindow::processAddGroup(uint8_t id)
{
    des.ieee_addr = currentIndex.data(ROLE_IEEE_ADDR).toULongLong();
    des.groupaddr = id;
    des.endpoint = currentIndex.data(ROLE_ENDPOINT).toUInt();
    gs_add_group(&des,id,"");
}

void MainWindow::processAddScene(uint8_t id)
{
    des.ieee_addr = currentIndex.data(ROLE_IEEE_ADDR).toULongLong();
    des.groupaddr = ui_selected_group;
    des.endpoint = currentIndex.data(ROLE_ENDPOINT).toUInt();
    gs_store_scene(&des,ui_selected_group,id);
}

void MainWindow::processRemoveGroup()
{
    gs_remove_from_group(&des,ui_selected_group);
}

void MainWindow::processRemoveScene()
{
    gs_remove_scene(&des,ui_selected_group,ui_selected_scene);
}

void MainWindow::initAction(){
    rightGroup = new QMenu("Group");
    rightSceneStore = new QMenu("Scene Store");
    rightBind = new QAction({tr("Bind")},this);
    rightSceneRecall = new QAction({tr("Scene Recall")},this);
    rightRemoveGroup = new QAction({tr("Remove Group")},this);
    rightRemoveScene = new QAction({tr("Remove Scene")},this);
    rightGroup_0 = new QAction({tr("Group 0")},this);
    rightGroup_1 = new QAction({tr("Group 1")},this);
    rightGroup_2 = new QAction({tr("Group 2")},this);
    rightGroup_3 = new QAction({tr("Group 3")},this);
    rightGroup_4 = new QAction({tr("Group 4")},this);
    rightGroup_5 = new QAction({tr("Group 5")},this);
    rightGroup_6 = new QAction({tr("Group 6")},this);
    rightGroup_7 = new QAction({tr("Group 7")},this);
    rightGroup_8 = new QAction({tr("Group 8")},this);
    rightGroup_9 = new QAction({tr("Group 9")},this);
    rightScene_0 = new QAction({tr("Scene 0")},this);
    rightScene_1 = new QAction({tr("Scene 1")},this);
    rightScene_2 = new QAction({tr("Scene 2")},this);
    rightScene_3 = new QAction({tr("Scene 3")},this);
    rightScene_4 = new QAction({tr("Scene 4")},this);
    rightScene_5 = new QAction({tr("Scene 5")},this);
    rightScene_6 = new QAction({tr("Scene 6")},this);
    rightScene_7 = new QAction({tr("Scene 7")},this);
    rightScene_8 = new QAction({tr("Scene 8")},this);
    rightScene_9 = new QAction({tr("Scene 9")},this);
    rightGroup->addAction(rightGroup_0);
    rightGroup->addAction(rightGroup_1);
    rightGroup->addAction(rightGroup_2);
    rightGroup->addAction(rightGroup_3);
    rightGroup->addAction(rightGroup_4);
    rightGroup->addAction(rightGroup_5);
    rightGroup->addAction(rightGroup_6);
    rightGroup->addAction(rightGroup_7);
    rightGroup->addAction(rightGroup_8);
    rightGroup->addAction(rightGroup_9);
    rightSceneStore->addAction(rightScene_0);
    rightSceneStore->addAction(rightScene_1);
    rightSceneStore->addAction(rightScene_2);
    rightSceneStore->addAction(rightScene_3);
    rightSceneStore->addAction(rightScene_4);
    rightSceneStore->addAction(rightScene_5);
    rightSceneStore->addAction(rightScene_6);
    rightSceneStore->addAction(rightScene_7);
    rightSceneStore->addAction(rightScene_8);
    rightSceneStore->addAction(rightScene_9);
}

void MainWindow::initConnect(){
    connect(ui->viewItem->selectionModel(),&QItemSelectionModel::currentChanged,this,&MainWindow::selectItem);
    connect(ui->viewItem,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenu(QPoint)));
    connect(modelProperty,&QStandardItemModel::itemChanged,this,&MainWindow::dataChange);

    connect(rightBind,&QAction::triggered,this,&MainWindow::processBind);

    connect(rightGroup_0,&QAction::triggered,this,[=]{ui_selected_group = 0; processAddGroup(0);});
    connect(rightGroup_1,&QAction::triggered,this,[=]{ui_selected_group = 1;processAddGroup(1);});
    connect(rightGroup_2,&QAction::triggered,this,[=]{ui_selected_group = 2;processAddGroup(2);});
    connect(rightGroup_3,&QAction::triggered,this,[=]{ui_selected_group = 3;processAddGroup(3);});
    connect(rightGroup_4,&QAction::triggered,this,[=]{ui_selected_group = 4;processAddGroup(4);});
    connect(rightGroup_5,&QAction::triggered,this,[=]{ui_selected_group = 5;processAddGroup(5);});
    connect(rightGroup_6,&QAction::triggered,this,[=]{ui_selected_group = 5;processAddGroup(6);});
    connect(rightGroup_7,&QAction::triggered,this,[=]{ui_selected_group = 6;processAddGroup(7);});
    connect(rightGroup_8,&QAction::triggered,this,[=]{ui_selected_group = 7;processAddGroup(8);});
    connect(rightGroup_9,&QAction::triggered,this,[=]{ui_selected_group = 8;processAddGroup(9);});

    connect(rightScene_0,&QAction::triggered,this,[=]{ui_selected_scene = 0;processAddScene(0);});
    connect(rightScene_1,&QAction::triggered,this,[=]{ui_selected_scene = 1;processAddScene(1);});
    connect(rightScene_2,&QAction::triggered,this,[=]{ui_selected_scene = 2;processAddScene(2);});
    connect(rightScene_3,&QAction::triggered,this,[=]{ui_selected_scene = 3;processAddScene(3);});
    connect(rightScene_4,&QAction::triggered,this,[=]{ui_selected_scene = 4;processAddScene(4);});
    connect(rightScene_5,&QAction::triggered,this,[=]{ui_selected_scene = 5;processAddScene(5);});
    connect(rightScene_6,&QAction::triggered,this,[=]{ui_selected_scene = 6;processAddScene(6);});
    connect(rightScene_7,&QAction::triggered,this,[=]{ui_selected_scene = 7;processAddScene(7);});
    connect(rightScene_8,&QAction::triggered,this,[=]{ui_selected_scene = 8;processAddScene(8);});
    connect(rightScene_9,&QAction::triggered,this,[=]{ui_selected_scene = 9;processAddScene(9);});
}

void MainWindow::initPropertyView()
{
    modelProperty->clear();
    for(int i = 0; i < 5; i++){
        QStandardItem *property = new QStandardItem;
        QStandardItem *value = new QStandardItem;
        QString string = listProperty[i];
        property->setData(string,Qt::DisplayRole);
        value->setData(string,ROLE_PROPERTY);
        property->setEditable(false);
        modelProperty->appendRow({property,value});
    }
}

void MainWindow::selectItem(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.data(ROLE_ITEM).toBool()){
        initPropertyView();
        currentIndex = current;
        qDebug() << "Item";
    }else{
        modelProperty->clear();
    }
}

void MainWindow::dataChange(QStandardItem *item)
{
    QString property = item->data(ROLE_PROPERTY).toString();
    des.ieee_addr = currentIndex.data(ROLE_IEEE_ADDR).toULongLong();
    des.groupaddr = currentIndex.data(ROLE_GROUP_ADDR).toUInt();
    des.endpoint = currentIndex.data(ROLE_ENDPOINT).toUInt();
    QVariant currentData = item->data(Qt::DisplayRole);
    if(property == listProperty[0]){
        if(item->data(Qt::DisplayRole).toInt() > 1 || item->data(Qt::DisplayRole).toInt() < 0){
            QMessageBox::warning(this,"Error Value","This value's only 0 or 1.");
            item->setData(currentData,Qt::DisplayRole);
            return;
        }
        act_set_onoff(&des,item->data(Qt::DisplayRole).toUInt());
    }
    if(property == listProperty[1]){
        if(item->data(Qt::DisplayRole).toInt() > 255 || item->data(Qt::DisplayRole).toInt() < 0){
            QMessageBox::warning(this,"Error Value","This value's only 0 or 255.");
            item->setData(currentData,Qt::DisplayRole);
            return;
        }
        act_set_level(&des,0,item->data(Qt::DisplayRole).toUInt());
    }
    if(property == listProperty[2]){
        if(item->data(Qt::DisplayRole).toInt() > 255 || item->data(Qt::DisplayRole).toInt() < 0){
            QMessageBox::warning(this,"Error Value","This value's only 0 or 255.");
            item->setData(currentData,Qt::DisplayRole);
            return;
        }
        QModelIndex indexSAT = modelProperty->index(item->row() + 1,COL_VALUE);
        act_set_color(&des,item->data(Qt::DisplayRole).toUInt(),indexSAT.data(Qt::DisplayRole).toUInt());
    }
    if(property == listProperty[3]){
        if(item->data(Qt::DisplayRole).toInt() > 255 || item->data(Qt::DisplayRole).toInt() < 0){
            QMessageBox::warning(this,"Error Value","This value's only 0 or 60.");
            item->setData(currentData,Qt::DisplayRole);
            return;
        }
        QModelIndex indexHUE = modelProperty->index(item->row() - 1,COL_VALUE);
        act_set_color(&des,indexHUE.data(Qt::DisplayRole).toUInt(),item->data(Qt::DisplayRole).toUInt());
    }
    if(property == listProperty[4]){
        if(item->data(Qt::DisplayRole).toInt() > 60 || item->data(Qt::DisplayRole).toInt() < 0){
            QMessageBox::warning(this,"Error Value","This value's only 0 or 60.");
            item->setData(currentData,Qt::DisplayRole);
            return;
        }
        comm_send_permit_join(item->data(Qt::DisplayRole).toUInt());
    }
}
