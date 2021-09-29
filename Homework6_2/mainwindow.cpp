#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getData(QString data, double dblvalue)
{
    ui->textBrowser->setText(data);

    ui->doubleSpinBox->setValue(dblvalue);
}

