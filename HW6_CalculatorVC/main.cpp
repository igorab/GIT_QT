#include "mainwindow.h"

#include <QApplication>

#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Calculator calc;

    w.show();

    return a.exec();
}
