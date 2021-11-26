#ifndef MATHOPERATOR_H
#define MATHOPERATOR_H

#include <QApplication>

class MathOperator
{
private:
    char op;
    int inputprecedence;
    int stackprecedence;


public:
    MathOperator();

    MathOperator(char ch);

    int operator >= (MathOperator a) const;

    void Evaluate(QStack<float> &OperandStack);

    char GetOp(void);
};

#endif // MATHOPERATOR_H
