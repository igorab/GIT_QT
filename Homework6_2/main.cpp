#include "dialog.h"

#include <QApplication>

void run()
{
    int i = 0;
    i++;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog       dialogWindow;

    run();

    dialogWindow.show();

    return a.exec();
}
