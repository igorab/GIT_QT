#include "circles.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Circles w;

    w.show();

    return a.exec();
}
