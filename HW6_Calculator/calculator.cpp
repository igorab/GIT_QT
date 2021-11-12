#include "calculator.h"

//Стандарт языка C++17
//Пример ввода: 8 9 + 1 7 - *

//______Реализация______

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

int pexpression()
{
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

    return 0;
}



Calculator::Calculator()
{
    pexpression();

}

int Calculator::reset()
{
    value1 = 0;
    value2 = 0;
    oper = 0;
    result = 0;

    return 0;
}

int Calculator::digit(int d)
{
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

    return 0;
}

int Calculator::operation(int _oper)
{
    oper = _oper;

    return 0;
}

int Calculator::calculate()
{
    switch(oper)
    {
        case 1:
            result = value1+ value2;
        break;
        case 2:
            result = value1 - value2;
            break;
        case 3:
            result = value1 * value2;
            break;
        case 4:
            result = value1/value2;
        break;
    }

    return 0;
}

QString Calculator::indicate()
{
    return QString::number(result);
}
