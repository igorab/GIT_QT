#include "mainwindow.h"
#include "ui_mainwindow.h"

//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modbusDevice = new QModbusTcpClient();

    if (modbusDevice)
    {
        connect(modbusDevice, &QModbusClient::stateChanged, this, &MainWindow::onStateChanged);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readReady()
{
    QModbusReply *lastRequest = qobject_cast<QModbusReply *>(sender());

    if (!lastRequest)
        return;

    if (lastRequest->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = lastRequest->result();

        ui->label_readdata->setText(QString::number(unit.value(0)));
    }
    else
    {
        ui->label_readdata->setText("Ошбка чтения");
    }

    lastRequest->deleteLater();
}


void MainWindow::on_pushButton_connect_clicked()
{
    new_connect_tcp(ui->lineEdit_address->text(), ui->spinBox_port->value());
}

void MainWindow::onStateChanged(int state)
{
    if (state == QModbusDevice::UnconnectedState)
    {
        ui->label_readdata->setText("Отключено");
    }
    else if (state == QModbusDevice::ConnectedState)
    {
        ui->label_readdata->setText("Подключено");
    }

}

void MainWindow::write_registr(int num_device, int reg, quint16 data)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, reg, 1);

    writeUnit.setValue(0, data);

    QModbusReply *lastResponse;

    lastResponse = modbusDevice->sendWriteRequest(writeUnit, num_device);

    if (!lastResponse->isFinished())
    {

    }
    else
    {
        lastResponse->deleteLater();
    }

}

void MainWindow::read_registr(int num_device, int reg, quint16 size)
{
    if (!modbusDevice)
    {
        return;
    }

    QModbusDataUnit readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, reg, size);

    if (auto *lastRequest = modbusDevice->sendReadRequest(readUnit, num_device))
    {
        if (!lastRequest->isFinished())
            connect(lastRequest, &QModbusReply::finished, this, &MainWindow::readReady);
        else
            lastRequest->deleteLater();
    }
    else
    {
        // ошибка чтения
    }


}

bool MainWindow::new_connect_tcp(const QString &address, int port)
{
    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        const QUrl url = QUrl::fromUserInput(address + ":" + QString::number(port));

        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

        if (!modbusDevice->connectDevice())
        {
            delete modbusDevice;

            modbusDevice = nullptr;

            return false;
        }
    }
}

void MainWindow::response()
{
    QModbusReply *lastRequest = qobject_cast<QModbusReply *>(sender());
}

void MainWindow::on_pushButton_read_clicked()
{
    read_registr(ui->spinBox_addr->value(), ui->spinBox_register->value(), 1);
}



