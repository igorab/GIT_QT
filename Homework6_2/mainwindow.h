#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//.... поместим его сюда

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


public slots:

    void getData(QString data, double dblvalue);

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
