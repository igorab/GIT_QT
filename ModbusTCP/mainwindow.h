#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusTcpClient>
#include <QUrl>

//  Чтение и запись Modbus +
//  Modbus slave +-

//обеспечивает возможности мастера modbus по последовательным интерфейсам
#include <QModbusRtuSerialMaster>
//обеспечивает работу с последовательными интерфейсами
#include <QSerialPort>
//получим информацию о всех последовательных интерфейсах в системе
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QModbusClient *modbusDevice = nullptr;

    ~MainWindow();

private slots:

    void readReady();
    void on_pushButton_connect_clicked();
    void on_pushButton_read_clicked();
//    void on_pushButton_write_clicked();

public slots:

    void onStateChanged(int state);

    void write_registr(int num_device, int reg, quint16 data);

    void read_registr(int num_device, int reg, quint16 size);

    bool new_connect_tcp(const QString &address, int port = 502);

    void response();

//    void disconnect();



private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
