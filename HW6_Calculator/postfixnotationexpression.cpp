#include "postfixnotationexpression.h"

PostfixNotationExpression::PostfixNotationExpression()
{
    standart_operators = { "(", ")", "+", "-", "*", "/", "^"};

    operators =  new QList<QString>(standart_operators);
}

///
/// \brief PostfixNotationExpression::Separate
/// \param input
/// \return
///
QString PostfixNotationExpression::Separate(QString input)
{
    int pos = 0;

    while (pos < input.length())
    {
        QString s = "" + input[pos];

        if (false == standart_operators.contains(QString(input[pos])))
        {
            if (input[pos].isDigit())
            {
                for (int i=pos+1;
                     i < input.length() && (input[i].isDigit() || input[i] == ',' || input[i] == '.');
                     i++ )
                {
                    s += input[i];
                }
            }
            else if (input[pos].isLetter() )
            {
                for (int i=pos+1; i<input.length() && (input[i].isLetter() || input[i].isDigit()); i++)
                {
                    s += input[i];
                }
            }
        }

        //yield return s;

        pos += s.length();
    }

    return "";
}

///
/// \brief PostfixNotationExpression::GetPriority
/// \param s
/// \return
///
qint8 PostfixNotationExpression::GetPriority(QString s)
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


///
/// \brief PostfixNotationExpression::ConvertToPostfixNotation
/// \param input
/// \return
///
QString PostfixNotationExpression::ConvertToPostfixNotation(QString input)
{
    QList<QString> *outputSeparated = new QList<QString>();

    //QStack<QString> *stack1 = new QStack<QString>();
    QStack<QString> stack;

    foreach (const QString &c, Separate(input))
    {
        if (operators->contains(c))
        {
            if (stack.count() > 0 && c != '(')
            {
                if (c == ')')
                {
                    QString s = stack.pop();

                    while (s != '(')
                    {
                        outputSeparated->append(s);

                        s = stack.pop();
                    }
                }
                else if (GetPriority(c) > GetPriority(stack.top()))
                {
                    stack.push(c);
                }
                else
                {
                    while (stack.count() > 0 && GetPriority(c) <= GetPriority(stack.top()))
                    {
                        outputSeparated->append(stack.pop());
                    }
                    stack.push(c);
                }
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

///
/// \brief PostfixNotationExpression::result
/// \param input
/// \return
///
qreal PostfixNotationExpression::result(QString input)
{
    QStack<QString> *stack = new QStack<QString>();

    QString postfixNotation = ConvertToPostfixNotation(input);

    QQueue<QString> *queue = new QQueue<QString>();
    queue->append(postfixNotation);

    QString str = queue->dequeue();

    while (queue->count() >= 0)
    {
        if (!operators->contains(str))
        {
            stack->push(str);
            str = queue->dequeue();
        }
        else
        {
            qreal summ = 0;

            try
            {
                if (str == "+")
                {
                    qreal a = 0;
                    qreal b = 0;

                    summ = a + b;
                }
                else if (str == "-")
                {
                    qreal a = 0;
                    qreal b = 0;

                    summ = b - a;
                }
                else if (str == "*")
                {
                    qreal a = 0;
                    qreal b = 0;

                    summ = b * a;
                }
                else if (str == "/")
                {
                    qreal a = 0;
                    qreal b = 0;

                    summ = b / a;
                }
                else if (str == "^")
                {
                    qreal a = 0;
                    qreal b = 0;

                    summ = pow(b, a);
                }

            }
            catch (char* msg)
            {

            }

            stack->push(QString::number(summ));

            if (queue->count() > 0)
            {
                str = queue->dequeue();
            }
            else
                break;
        }
    }

    return stack->pop().toFloat();
}




