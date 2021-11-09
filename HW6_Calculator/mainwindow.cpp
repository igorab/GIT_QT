#include "mainwindow.h"
#include "ui_frmCalculator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::frmCalculator)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

