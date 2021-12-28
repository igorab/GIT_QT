#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include "postfixnotationexpression.h"

const char leftparenthesis = '(';
const char rightparenthesis = ')';

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

    int oper;
    double result;

};

#endif // CALCULATOR_H
