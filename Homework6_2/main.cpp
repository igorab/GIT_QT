#include "dialog.h"

#include <QApplication>

// Homework 6-2
// Создайте программу, которая выводит на экран окно и требует от пользователя ввести число.
// После нажатия кнопки "ОК" -это число должно быть отображено в следующем открывшемся окне.


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog       dialogWindow;

    dialogWindow.show();

    return a.exec();
}
