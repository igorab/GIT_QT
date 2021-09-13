#ifndef PID_H
#define PID_H

class PID
{
public:
    PID();
    float output = 0;

    float operate(float sensor){

        delta = sp - sensor;

        prop = delta * kp;

        if (output >= 0 && output <= 100) integral += delta *(1/ki);

        diff = (delta - delta1) * kd;
        delta1 = delta;

        output = prop + integral + diff;

        if (output > 100) output = 100;
        if (output < 0 ) output = 0;

        return output;
    }

private:
    float kp = 5;
    float ki = 100;
    float kd = 20;

    float delta;
    float delta1;
    float sp = 55;
    float integral = 0;
    float diff = 0;
    float prop = 0;

};


#endif // PID_H
