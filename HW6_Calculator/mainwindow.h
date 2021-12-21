#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class frmCalculator; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_But_0_clicked();

    void on_But_1_clicked();
    void on_But_2_clicked();
    void on_But_3_clicked();
    void on_But_4_clicked();
    void on_But_5_clicked();
    void on_But_6_clicked();
    void on_But_7_clicked();
    void on_But_8_clicked();
    void on_But_9_clicked();


    void on_But_C_clicked();

    void on_But_Plus_clicked();

    void on_But_Min_clicked();

    void on_But_Mul_clicked();

    void on_But_Div_clicked();

    void on_But_E_clicked();

    void on_But_Pow_clicked();

    void on_But_LeftParenthesis_clicked();

    void on_But_RightParenthesis_clicked();

    void on_But_DelChar_clicked();

private:
    Ui::frmCalculator *ui;
};
#endif // MAINWINDOW_H
