#include <QCoreApplication>

#include <QFile>
#include <iostream>

#include "pid.h"
#include "pwm.h"
#include "sensor.h"

// homework 5-0

#include "stat.h"
/*
 * Реализовать: симулятор датчика, регулятора и ШИМ
 *
 * Реализовать программу, которая открывает полученный файл и анализирует его
 *
 *1. Определить максимальный выбег перерегулирования за уставку.
 *  Т.е.когда температура первый раз превысила уставку-определить, какое отклонение в плюс и вминус было максимальным от этого момента до конца работы программы.
 *
 *2. Определяет количество разворотов тренда.Т.е.когда контролируемая величина (температура) меняет направление своего движения.
 *  Т.е. если росла и стала падать – это засчитывается за 1. Если падала и стала расти – это ещё 1.
 *
 *3. Определить время выхода на уставку.
 *   Для этого необходимо взять точки разворота тренда из пункта 2 и определить,
 *   в какой наиболее ранний момент разница между верхней точкой перелома и нижней стала меньше трёх градусов
 *
 * */

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Sensor temperature;
    PID regulator;
    PWM pwm;

    QFile file("data.csv");

    file.open(QIODevice::ReadWrite | QIODevice::Truncate);

    file.write("Temperature;Regulator\n");

    for (int i=0; i<2000; i++)
    {
        regulator.operate(temperature.output); // Запустили регулятор - на вход регулятора подали выход симулятора температуры
        pwm.operate(regulator.output); // запуск ШИМ
        temperature.simulate(pwm.state); // запуск симуляции температуры

        QString data = QString::number(temperature.output) + ";" + QString::number(regulator.output) + "\n";
        file.write(data.toStdString().c_str());

        cout << "t= " << temperature.output << " r= " << regulator.output << " s= " << pwm.state << endl;
    }

    file.close();

    cout << "analyze the resulting file" << endl;

    // анализируем полученный файл
    Stat st;
    st.sp = regulator.sp;

    st.calc();

    cout << "number of trend reversals: " << st.trendReversal << endl;

    return 0;
}
