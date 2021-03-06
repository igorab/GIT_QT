#ifndef POSTFIXNOTATIONEXPRESSION_H
#define POSTFIXNOTATIONEXPRESSION_H

#include "QApplication"
#include <QStack>
#include <QQueue>
#include <QtMath>
#include <QVector>
#include <stdlib.h>
#include <list>

class PostfixNotationExpression
{   
public:

    PostfixNotationExpression();

    QList<QString> *ConvertToPostfixNotation(QString input, QString *errTxt);

    qreal result(QString input, QString *errTxt);

    QString ReversePolishNotation;

    enum opError{
        OperatorExpected,
        OperandExpected,
        MissingLeftParenthesis,
        MissingRightParenthesis,
        InvalidInput
    };

    QString errorTxt(int n);

private:

    QList<QString> standart_operators;
    QList<QString> *operators;

    void Separate(QString input, QVector<QString> &resVector);

    qint8 GetPriority(QString s);

};

#endif // POSTFIXNOTATIONEXPRESSION_H
