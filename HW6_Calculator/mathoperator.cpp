#include "mathoperator.h"

MathOperator::MathOperator()
{

}

MathOperator::MathOperator(char ch)
{
    op = ch;

    switch (op)
    {
        case '+':
        case '-':
            inputprecedence = 1;
            stackprecedence = 1;
        break;

        case '*':
        case '/':
            inputprecedence = 2;
            stackprecedence = 2;
        break;

        case '(':
            inputprecedence = 3;
            stackprecedence = -1;
        break;

        case ')':
            inputprecedence = 0;
            stackprecedence = 0;
        break;

    }
}

int MathOperator::operator >=(MathOperator a) const
{
    return stackprecedence >= a.inputprecedence;
}

void MathOperator::Evaluate(QStack<float> &OperandStack)
{
    float operand1 = OperandStack.pop();
    float operand2 = OperandStack.pop();

    switch(op)
    {
    case '+':
        OperandStack.push(operand1 + operand2);
        break;
    case '-':
        OperandStack.push(operand2 - operand1);
        break;
    case '*':
        OperandStack.push(operand1 * operand2);
        break;
    case '/':
        OperandStack.push(operand2/operand1);
        break;
    }
}

char MathOperator::GetOp()
{

}
