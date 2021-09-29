#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    mainwindow = new MainWindow();

    connect(this, SIGNAL(sendData(QString,double)), mainwindow, SLOT(getData(QString,double)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *qe)
{

    data = ui->plainTextEdit->toPlainText();

    double dblvalue  = ui->doubleSpinBox->value();

    emit sendData(data, dblvalue);
}

void Dialog::on_buttonBox_rejected()
{
    this->close();
}

void Dialog::on_buttonBox_accepted()
{
    mainwindow->show();

    this->close();
}

