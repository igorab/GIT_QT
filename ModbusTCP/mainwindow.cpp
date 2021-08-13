#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modbusDevice = new QModbusTcpClient();

    if (modbusDevice) connect(modbusDevice, &QModbusClient::stateChanged, this, &MainWindow::onStateChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_connect_clicked()
{
    //new_connect_tcp(ui->lineEdit_address->text(), ui->spinBox_port->value());
}

