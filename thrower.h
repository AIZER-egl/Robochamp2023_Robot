#include <Arduino.h>

#ifndef THROWER_H
#define THROWER_H

#define MOTOR_A 10
#define MOTOR_B 9

class Thrower {
    private:
    public:
        Thrower ();
        void shoot ();
        void stop ();
};

#endif