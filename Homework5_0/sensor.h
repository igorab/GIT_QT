#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{


public:
    Sensor();

    float output = 0;

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
    float power = 0;
    float inertia = 200;
    float speed = 0.1;
    float heating;

};







#endif // SENSOR_H
