#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include "postfixnotationexpression.h"

class Calculator
{

public:
    Calculator();

    QString expression;
    QString reverseExpression;

    int reset();    
    int digit(int d);
    int operation(char op);
    float calculate();
    QString indicate();

private:

    double value1;
    double value2;

    int oper;
    double result;

};

#endif // CALCULATOR_H
