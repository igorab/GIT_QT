#include "postfixnotationexpression.h"

QString PostfixNotationExpression::errorTxt(int n)
{
    const static char *errormsgs[] =
    {
        "Отсутствует оператор",
        "Отсутствует операнд",
        "Нет левой скобки",
        "Нет правой скобки",
        "Неверный ввод"
    };

    return errormsgs[n];
}

PostfixNotationExpression::PostfixNotationExpression()
{
    standart_operators = { "(", ")", "+", "-", "*", "/", "^"};

    operators =  new QList<QString>(standart_operators);
}

///
/// \brief PostfixNotationExpression::Separate
/// \param input
///  input string expression to parse
/// \param resVector
/// result vector parsed string
///
void PostfixNotationExpression::Separate(QString input, QVector<QString> &resVector)
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

        resVector.append(s);

        pos += s.length();
    }
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
QList<QString>* PostfixNotationExpression::ConvertToPostfixNotation(QString input)
{
    QList<QString> *outputSeparated = new QList<QString>();

    QStack<QString> *stack = new QStack<QString>();
    QVector<QString>  qVector;

    Separate(input, qVector);

    for (const QString &c: qAsConst(qVector))
    {
        if (operators->contains(c))
        {
            if (stack->count() > 0 && c != '(')
            {
                if (c == ')')
                {
                    QString s = stack->pop();

                    while (s != '(')
                    {
                        outputSeparated->append(s);

                        s = stack->pop();
                    }
                }
                else if (GetPriority(c) > GetPriority(stack->top()))
                {
                    stack->push(c);
                }
                else
                {
                    while (stack->count() > 0 && GetPriority(c) <= GetPriority(stack->top()))
                    {
                        outputSeparated->append(stack->pop());
                    }
                    stack->push(c);
                }
            }
            else
            {
                stack->push(c);
            }
        }
        else
        {
            outputSeparated->append(c);
        }
    }

    while (!stack->isEmpty())
    {                        
        outputSeparated->append(stack->pop());
    }

    delete stack;

    return outputSeparated;
}

///
/// \brief PostfixNotationExpression::result
/// \param input
/// \return
///
qreal PostfixNotationExpression::result(QString input, QString *errTxt)
{
    *errTxt = "";
    QStack<QString> *stack = new QStack<QString>();

    QList<QString> *listRPN = ConvertToPostfixNotation(input);

    foreach(QString word, *listRPN)
    {
        ReversePolishNotation += " " + word;
    }

    QQueue<QString> *queue = new QQueue<QString>();
    queue->append(*listRPN);

    delete listRPN;

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

            if (str == "+")
            {
                qreal a = 0, b = 0;
                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    a = stack->pop().toDouble();

                if (stack->isEmpty())
                {
                    *errTxt =  errorTxt(OperandExpected);
                    return 0;
                }
                else
                    b = stack->pop().toDouble();

                summ = a + b;
            }
            else if (str == "-")
            {
                qreal a = 0, b = 0;
                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    a = stack->pop().toDouble();

                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    b = stack->pop().toDouble();

                summ = b - a;
            }
            else if (str == "*")
            {
                qreal a = 0, b = 0;
                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    a = stack->pop().toDouble();

                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    b = stack->pop().toDouble();

                summ = b * a;
            }
            else if (str == "/")
            {
                qreal a = 0, b = 0;
                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    a = stack->pop().toDouble();

                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    b = stack->pop().toDouble();

                summ = b / a;
            }
            else if (str == "^")
            {
                qreal a = 0, b = 0;
                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    a = stack->pop().toDouble();

                if (stack->isEmpty())
                {
                    *errTxt = errorTxt(OperandExpected);
                    return 0;
                }
                else
                    b = stack->pop().toDouble();

                summ = pow(b, a);
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

     qreal ret = stack->pop().toFloat();

    delete stack;

    return ret;
}




