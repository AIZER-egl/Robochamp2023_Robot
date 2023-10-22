#include <Arduino.h>
#include <Servo.h>

#ifndef CRAW_H
#define CRAW_H

#define SERVO_LEFT 13
#define SERVO_RIGHT 12

#define SERVO_OPEN 110
#define SERVO_CLOSE 170

#define DELAY 1000

class Craw {
    private:
        Servo servoLeft;
        Servo servoRight;

        unsigned long triggeredTime;
        unsigned long elapsedTime;
        bool currentState;
    public:
        Craw ();
        void toggle();
        void fopen();
        void fclose();
};

#endif