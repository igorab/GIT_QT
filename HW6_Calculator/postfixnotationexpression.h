#ifndef POSTFIXNOTATIONEXPRESSION_H
#define POSTFIXNOTATIONEXPRESSION_H

#include "QApplication"
#include <QStack>
#include <QQueue>
#include <QtMath>

class PostfixNotationExpression
{   
public:
    PostfixNotationExpression();

    QString ConvertToPostfixNotation(QString input);

    qreal result(QString input);



private:

    QList<QString> standart_operators;
    QList<QString> *operators;

    QString Separate(QString input);

    qint8 GetPriority(QString s);





};

#endif // POSTFIXNOTATIONEXPRESSION_H
