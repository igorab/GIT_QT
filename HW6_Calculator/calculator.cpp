#include "calculator.h"

Calculator::Calculator()
{


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
