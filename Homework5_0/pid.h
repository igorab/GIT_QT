#ifndef PID_H
#define PID_H

class PID
{
public:
    PID();
    float output = 0;

    float operate(float sensor)
    {

        delta = sp - sensor; // уставка минус показатель датчика

        prop = delta * kp; // пропорциональная составляющая

        if (output >= 0 && output <= 100) integral += delta *(1/ki);

        diff = (delta - delta1) * kd;
        delta1 = delta;

        output = prop + integral + diff; // сумма всех регуляторов

        if (output > 100) output = 100; // мин-макс output
        if (output < 0 ) output = 0;

        return output;
    }

    float sp = 51; // уставка регулятора

private:
    // коэффициенты PID
    float kp = 5;
    float ki = 100;
    float kd = 20;

    float delta = 0; // дельта
    float delta1 = 0; // старая дельта
    float integral = 0; // накопленная интегральная составляющая
    float diff = 0;
    float prop = 0;

};


#endif // PID_H
