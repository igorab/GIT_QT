#include "mathoperator.h"
#include <stdlib.h>
#include <iostream>
#include <ctype.h>

#include <iostream>
using namespace std;

//#pragma hdrstop

const char leftparenthesis = '(';
const char rightparenthesis = ')';

enum operror{
    OperatorExpected,
    OperandExpected,
    MissingLeftParenthesis,
    MissingRightParenthesis,
    InvalidInput
};

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

void runcalc()
{
    QStack<MathOperator> OperatorStack;

    QStack<float> OperandStack;

    MathOperator opr1, opr2;

    int rank = 0;
    float number;
    char ch;

    while (cin.get(ch) && ch != '=')
    {
        if (isdigit(ch) || ch == '.')
        {
            cin.putback(ch);
            cin >> number;

            rank ++;

            if (rank > 1)
                error(OperatorExpected);

            OperandStack.push(number);
        }
        else if (isoperator(ch))
        {
            if (ch !='(') // ранг ' (' равен 0
                rank--;

            if (rank < 0)
                error(OperandExpected);

            opr1 = MathOperator(ch);

            while(!OperatorStack.empty() && ((opr2 = OperandStack.top()) >= opr1))
            {
                opr2 = OperatorStack.pop() ;

                opr2.Evaluate(OperandStack);
            }
            OperatorStack.push(opr1);

        }
        else if (ch == rightparenthesis)
        {
            opr1 = MathOperator(ch);

            while(!OperatorStack.empty() && (opr2 = OperatorStack.top()) >= opr1)
            {
                opr2 = OperatorStack.pop();
                opr2.Evaluate(OperandStack);
            }

            if (OperatorStack.empty())
                error(MissingLeftParenthesis);

            opr2 = OperatorStack.pop(); // get rid of ' ('
        }
        else if (iswhitespace(ch))
        {
            error(InvalidInput);
        }
    }

    if (rank != 1)
        error(OperandExpected);

    while (!OperatorStack.empty())
    {
        opr1 = OperatorStack.pop();

        if (opr1.GetOp()== leftparenthesis)
            error(MissingRightParenthesis);

        opr1.Evaluate(OperandStack);
    }

    cout << "Значение равно: " << OperandStack.pop() << endl;
}

