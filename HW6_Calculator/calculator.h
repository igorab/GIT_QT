#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include "postfixnotationexpression.h"

class Calculator
{

public:
    Calculator();

    int reset();
    int digit(int d);
    int operation(int o);
    int calculate();
    QString indicate();

private:

    double value1;
    double value2;

    int oper;
    double result;

};

#endif // CALCULATOR_H
