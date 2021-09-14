#ifndef SENSOR_H
#define SENSOR_H


class Sensor
{
    // матемаическая модель - симуляция графика температуры

public:
    Sensor();

    float output = 0;

    // heat - признак включен или нет нагрев
    float simulate(int heat)
    {
        if (heat)
        {
            power ++;
        }
        else
        {
            power --;
        }

        if (power>inertia) power = inertia;

        if (power<0) power = 0;

        heating = 100 / inertia * power * speed;

        output += heating - (output * speed *0.6);
        return output;
    }


private:
    float power = 0;  // мощность от 0 до 100
    float inertia = 200; // инерция
    float speed = 0.1;
    float heating; // какое происходит изменение температуры за цикл

};







#endif // SENSOR_H
