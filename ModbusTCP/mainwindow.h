#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void onStateChanged(int state);

public slots:

    void write_registr(int num_device, int reg, quint16 data);



private:
    Ui::MainWindow *ui;
};

inline void MainWindow::onStateChanged(int state)
{

}

inline void MainWindow::write_registr(int num_device, int reg, quint16 data)
{

}
#endif // MAINWINDOW_H
