#include "uiconnection.h"
#include "ui_uiconnection.h"

Q_DECLARE_METATYPE(network_info_t)
Q_DECLARE_METATYPE(device_info_t)

uiconnection::uiconnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uiconnection)
{
    ui->setupUi(this);
    initInput();
    //Set default
    ui->inputNwkNanagerServerHostname->setText("127.0.0.1");
    ui->inputNwkManagerServerPort->setText("2540");
    ui->inputGatewayServerHostname->setText("127.0.0.1");
    ui->inputGatewayServerPort->setText("2541");
    ui->inputOtaServerHostname->setText("127.0.0.1");
    ui->inputOstaServerPort->setText("2525");
}

uiconnection::~uiconnection()
{
    delete ui;
}

void uiconnection::receiveNetwork(QVariant ds_network)
{
    ui->buttonConnect->setText("Disconnect");
    uiconnection::hide();
}

void uiconnection::on_buttonConnect_clicked()
{
    emit startConnect(ui->inputNwkNanagerServerHostname->text().toUtf8().constData(),ui->inputNwkManagerServerPort->text().toUShort(),
                      ui->inputGatewayServerHostname->text().toUtf8().constData(),ui->inputGatewayServerPort->text().toUShort(),
                      ui->inputOtaServerHostname->text().toUtf8().constData(),ui->inputOstaServerPort->text().toUShort());
}

void uiconnection::on_buttonCancel_clicked()
{
    uiconnection::hide();
}

void uiconnection::initInput()
{
    ui->inputOstaServerPort->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),ui->inputOstaServerPort));
    ui->inputGatewayServerPort->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),ui->inputGatewayServerPort));
    ui->inputNwkManagerServerPort->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),ui->inputNwkManagerServerPort));
}
