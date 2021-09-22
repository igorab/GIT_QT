#ifndef STAT_H
#define STAT_H
#include <QFile>
#include <QTextStream>
#include <iostream>

class Stat
{
private:
    int cnt = 0;
    bool overHeat = false;
    float maxTemp0 = 0, minTemp0 = 0;
    float maxTemp = 0, minTemp = 0;

public:
    Stat();

    float sp = 0; // уставка

    int trendReversal = 0;

    void calc();
    void process_line(QString line, float &, float &);
};

#endif // STAT_H
