#include <QCoreApplication>
#include <iostream>
#include "calculator.cpp"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //return a.exec();

    //Calculator calculator;

    //runcalc();

    char ch;
    std::cout << "enter value:" <<  std::endl;
    std::cin >> ch;

    std::cout << "calculation result:" << ch << std::endl;
    return 0;

}
