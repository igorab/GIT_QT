#include "calculator.h"
#include <stdlib.h>
#include <iostream>
#include <ctype.h>

#include <iostream>
using namespace std;

//#pragma hdrstop

int isoperator(char ch)
{
    if (ch =='+' || ch == '-' || ch == '*' ||   ch == '/' || ch == '(')
        return 1;
    else
        return 0;
}

int iswhitespace(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return 1;
    else
        return 0;
}

enum operror{
    OperatorExpected,
    OperandExpected,
    MissingLeftParenthesis,
    MissingRightParenthesis,
    InvalidInput
};

void error(int n)
{
    const static char *errormsgs[] = {
        "Отсутствует оператор",
        "Отсутствует операнд",
        "Нет левой скобки",
        "Нет правой скобки",
        "Неверный ввод"};

    cerr << errormsgs[n]<< endl;

    exit(1);
}

Calculator::Calculator()
{
    expression = "";
    reverseExpression = "";
}

int Calculator::reset()
{
    expression = "";
    reverseExpression = "";

    oper = 0;
    result = 0;

    return 0;
}

int Calculator::digit(int d)
{
    expression += QString::number(d);
    return 0;
}

int Calculator::operation(char _oper)
{
    if (_oper == 0x08)
    {
        expression = expression.left(expression.length()-1);
    }
    else
    {
        expression += QChar(_oper);
    }

    return 0;
}

float Calculator::calculate()
{
    PostfixNotationExpression pnexpr;

    result = pnexpr.result(expression); //"2-2*(3-1+(3+4-2*6))"
    reverseExpression = pnexpr.ReversePolishNotation;

    return result;
}

QString Calculator::indicate()
{
    return expression;
}
