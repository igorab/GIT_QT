#include "stat.h"

Stat::Stat()
{

}

/*
 *1. Определить максимальный выбег перерегулирования за уставку.
 *  Т.е.когда температура первый раз превысила уставку-определить, какое отклонение в плюс и в минус было максимальным
 *  от этого момента до конца работы программы.
 *
 *2. Определяет количество разворотов тренда.Т.е.когда контролируемая величина (температура) меняет направление своего движения.
 *  Т.е. если росла и стала падать – это засчитывается за 1. Если падала и стала расти – это ещё 1.
 *
 *3. Определить время выхода на уставку.
 *   Для этого необходимо взять точки разворота тренда из пункта 2 и определить,
 *   в какой наиболее ранний момент разница между верхней точкой перелома и нижней стала меньше трёх градусов
 *
*/

float prevTemp = 0;

int trendUpDown = 0;
int prevTrend = 0;

float tempTrendRev = 0;
float tempFrom = 0;
float tempTo = 0;


void Stat::process_line(QString line, float &maxDeltaTemp, float &minDeltaTemp)
{   
    QStringList list =  line.split(";", Qt::SkipEmptyParts);

    float xTemp = 0, yReg = 0;

    xTemp = list[0].toFloat(); // current temperature

    if (prevTemp <= xTemp) // температура растет
    {
        trendUpDown = 1; // UP
    }
    else
    {
        trendUpDown = 2;
    }

    if (prevTrend != trendUpDown && prevTrend != 0)
    {
        // значит произошел разворот тренда

        trendReversalQty ++;

        if (cntSetPoint == 0)
        {
            if (abs(tempTrendRev - xTemp) < 3.0 )
            {
                cntSetPoint = cnt;
            }
            else
            {
                tempTrendRev = xTemp;
            }
        }
    }

    prevTrend = trendUpDown;
    prevTemp  = xTemp;

    yReg = list[1].toFloat(); // regulator

    if (overHeat == false)
    {
        if (xTemp > sp)
        {
            maxTemp0 = maxTemp = xTemp;
            minTemp0 = minTemp = xTemp;

            overHeat = true; // температура первый раз превысила уставку
        }
    }

    if (overHeat == true)
    {
        if (xTemp > maxTemp)
        {
            maxTemp = xTemp;
            maxDeltaTemp =  maxTemp - maxTemp0;
        }

        if (xTemp < minTemp)
        {
            minTemp = xTemp;
            minDeltaTemp =  minTemp0 - minTemp;
        }
    }
}

void Stat::calc()
{
    QFile file("data.csv");

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

    overHeat = false;

    while (!file.atEnd())
    {
        QString line = file.readLine();

        if (cnt > 0)
        {
            this->process_line(line, MaxDeltaTemperature, MinDeltaTemperature );
        }

        cnt ++;
    }    

    file.close();
}
