#include "calculator.h"
#include "mathoperator.h"

#include <stdlib.h>
#include <iostream>
#include <ctype.h>

#include <iostream>
using namespace std;

//#pragma hdrstop

const char leftparenthesis = '(';
const char rightparenthesis = ')';

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


//Стандарт языка C++17
//Пример ввода: 8 9 + 1 7 - *

//______Реализация______
/*
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <cctype>
*/
//using namespace std;

int pexpression()
{
    /*
    map<char, function<int64_t(const int64_t&, const int64_t&)>> operations;

    operations['+'] = [](const int64_t& a, const int64_t& b) constexpr { return a + b; };
    operations['-'] = [](const int64_t& a, const int64_t& b) constexpr { return a - b; };
    operations['*'] = [](const int64_t& a, const int64_t& b) constexpr { return a * b; };
    operations['/'] = [](const int64_t& a, const int64_t& b) constexpr { return a / b; };

    string expression;

    vector<int64_t> stack_;

    int64_t number = 0;

    bool flag = true;

    getline(cin, expression);

    for (const auto& i : expression)
    {
        if (isdigit(i))
        {
            number *= 10;
            number += (i - '0');
            flag = true;
        }
        else
        {
            if (i != ' ')
            {
                int64_t num2 = stack_.back();
                stack_.pop_back();
                int64_t num1 = stack_.back();
                stack_.pop_back();

                stack_.push_back(operations[i](num1, num2));
                flag = false;
            }
            else if (i == ' ' && flag)
            {
                stack_.push_back(number);
                number = 0;
            }
        }
    }

    cout << stack_.back();
    */
    return 0;
}


Calculator::Calculator()
{
    expression = "";

    pexpression();

}

int Calculator::reset()
{
    expression = "";

    value1 = 0;
    value2 = 0;
    oper = 0;
    result = 0;

    return 0;
}


int Calculator::digit(int d)
{
    expression += QString::number(d);

    /*
    if (oper == 0)
    {
        value1 = value1*10 + d;
        result = value1;
    }
    else
    {
        value2 = value2 * 10 +d;
        result = value2;
    }
    */
    return 0;
}

int Calculator::operation(char _oper)
{
    expression += QChar(_oper);

    //oper = _oper;

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
    return expression; //QString::number(result);
}
