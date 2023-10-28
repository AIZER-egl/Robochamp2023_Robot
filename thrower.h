#include <Arduino.h>
#include <Servo.h>

#ifndef THROWER_H
#define THROWER_H

#define MOTOR_A 10
#define MOTOR_B 9

#define SERVO_DOOR 8

class Thrower {
    private:
        Servo servo;
    public:
        Thrower ();
        void shoot ();
        void stop ();
};

#endif