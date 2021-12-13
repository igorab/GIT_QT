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
        }
    }
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

        }

        pos += s.length();
    }
}

///
/// \brief GetPriority
/// \param s
/// \return
///
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
