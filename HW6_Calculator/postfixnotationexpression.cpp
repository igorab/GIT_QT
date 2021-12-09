#include "postfixnotationexpression.h"

PostfixNotationExpression::PostfixNotationExpression()
{
    standart_operators = { "(", ")", "+", "-", "*", "/", "^"};

    operators =  new QList<QString>(standart_operators);
}

QString PostfixNotationExpression::ConvertToPostfixNotation(QString input)
{
    QList<QString> *outputSeparated = new QList<QString>();

    //QStack<QString> *stack1 = new QStack<QString>();
    QStack<QString> stack;

    foreach (const QString &c, Separate(input))
    {
        if (operators->contains(c))
        {
            if (stack.count() > 0)
            {

            }
            else
            {
                stack.push(c);
            }
        }
        else
        {
            outputSeparated->append(c);
        }

    }

}

QString PostfixNotationExpression::Separate(QString input)
{
    int pos = 0;

    while (pos < input.length())
    {
        QString s = "" + input[pos];


        if (false == standart_operators.contains(QString(input[pos])))
        {

        }

        pos += s.length();
    }
}

qint8 GetPriority(QString s)
{
    if (s == "(" || s ==")")
         return 0;
    else if (s == "+" || s =="-")
        return 1;
    else if (s == "*" || s =="/")
        return 2;
    else if (s == "^")
        return 3;
    else
        return 4;

}
