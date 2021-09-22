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
int trendChangeQty = 0;

int trendUpDown = 0;
int prevTrend = 0;

void Stat::process_line(QString line, float &maxDeltaTemp, float &minDeltaTemp)
{   
    QStringList list =  line.split(";", Qt::SkipEmptyParts);

    if (cnt > 0)
    {
        float xTemp = 0, yReg = 0;

        xTemp = list[0].toFloat(); // temperature

        if (prevTemp >= xTemp)
        {
            trendUpDown = 1;
        }
        else
        {
            trendUpDown = 2;
        }

        if (prevTrend != trendUpDown)
        {
            trendChangeQty ++;
        }

        prevTrend = trendUpDown;
        prevTemp = xTemp;

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

        //std::cout << xTemp << " ; " << yReg << std::endl;

        // Точки разворота тренда :



        // Время выхода на уставку :

    }

    cnt ++;
}

void Stat::calc()
{
    QFile file("data.csv");

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

    float maxDeltaTemp = 0, minDeltaTemp = 0;

    overHeat = false;

    while (!file.atEnd())
    {
        QString line = file.readLine();

        this->process_line(line, maxDeltaTemp, minDeltaTemp );
    }

    std::cout << "Max delta temp: " << maxDeltaTemp << std::endl;
    std::cout << "Min delta temp: " << minDeltaTemp << std::endl;

    float trendRevQty =0;
    std::cout << "Trend reversals quantity: " <<  trendRevQty << std::endl;

    float qSetPoint = 0;
    std::cout << "Setpoint quantity: " << qSetPoint << std::endl;


    file.close();
}
