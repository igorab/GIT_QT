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

void MainWindow::ClickDigit(int _digit)
{
    calculator.digit(_digit);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_0_clicked()
{    
    ClickDigit(0);
}

void MainWindow::on_But_1_clicked()
{
    ClickDigit(1);
}

void MainWindow::on_But_2_clicked()
{
    ClickDigit(2);
}

void MainWindow::on_But_3_clicked()
{
    ClickDigit(3);
}

void MainWindow::on_But_4_clicked()
{
    ClickDigit(4);
}

void MainWindow::on_But_5_clicked()
{
    ClickDigit(5);
}

void MainWindow::on_But_6_clicked()
{
    ClickDigit(6);
}

void MainWindow::on_But_7_clicked()
{
    ClickDigit(7);
}

void MainWindow::on_But_8_clicked()
{
    ClickDigit(8);
}

void MainWindow::on_But_9_clicked()
{
    ClickDigit(9);
}

///
/// \brief MainWindow::on_But_C_clicked
/// clear
///
void MainWindow::on_But_C_clicked()
{
    calculator.reset();
    ui->CalcScreen->setText(calculator.indicate());
    ui->CalcRPN->setText("");
    ui->CalcResult->setText("");

}

void MainWindow::on_But_Plus_clicked()
{
    calculator.operation('+');
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_Min_clicked()
{
    calculator.operation('-');
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_Mul_clicked()
{
    calculator.operation('*');
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_Div_clicked()
{
    calculator.operation('/');
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_Pow_clicked()
{
    calculator.operation('^');
    ui->CalcScreen->setText(calculator.indicate());
}

///
/// \brief MainWindow::on_But_E_clicked
/// вычислить выражение (=)
///
void MainWindow::on_But_E_clicked()
{
    float result = calculator.calculate();
    ui->CalcResult->setText(QString::number(result));
    ui->CalcRPN->setText(calculator.reverseExpression);
}

void MainWindow::on_But_LeftParenthesis_clicked()
{
    calculator.operation(leftparenthesis);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_RightParenthesis_clicked()
{
    calculator.operation(rightparenthesis);
    ui->CalcScreen->setText(calculator.indicate());
}

void MainWindow::on_But_DelChar_clicked()
{
    calculator.operation(0x08);
    ui->CalcScreen->setText(calculator.indicate());
}

