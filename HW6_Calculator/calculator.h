#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>

class Calculator
{

public:
    Calculator();

    int reset();
    int digit(int d);
    int operation(int o);
    int calculate();
    QString indicate();


};

#endif // CALCULATOR_H
