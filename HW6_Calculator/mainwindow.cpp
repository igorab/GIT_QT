#include "mainwindow.h"
#include "ui_frmCalculator.h"
#include "calculator.h"

Calculator   calculator;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::frmCalculator)
{

    ui->setupUi(this);

    calculator.reset();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_But_0_clicked()
{
    calculator.digit(0);
    ui->CalcScreen->setText(calculator.indicate());
}


void MainWindow::on_But_1_clicked()
{
    calculator.digit(1);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_2_clicked()
{
    calculator.digit(2);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_3_clicked()
{
    calculator.digit(3);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_4_clicked()
{
    calculator.digit(4);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_5_clicked()
{
    calculator.digit(5);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_6_clicked()
{
    calculator.digit(6);
    ui->CalcScreen->setText(calculator.indicate());
}
void MainWindow::on_But_7_clicked()
{
    calculator.digit(7);
    ui->CalcScreen->setText(calculator.indicate());
}
void MainWindow::on_But_8_clicked()
{
    calculator.digit(8);
    ui->CalcScreen->setText(calculator.indicate());
}
void MainWindow::on_But_9_clicked()
{
    calculator.digit(9);
    ui->CalcScreen->setText(calculator.indicate());
}


void MainWindow::on_But_C_clicked()
{
    calculator.reset();
    ui->CalcScreen->setText(calculator.indicate());
}


void MainWindow::on_But_Plus_clicked()
{
    calculator.operation(1);
}


void MainWindow::on_But_Min_clicked()
{
    calculator.operation(2);
}


void MainWindow::on_But_Mul_clicked()
{
    calculator.operation(3);
}


void MainWindow::on_But_Div_clicked()
{
    calculator.operation(4);
}


void MainWindow::on_But_E_clicked()
{
    calculator.calculate();

    ui->CalcScreen->setText(calculator.indicate());
}

