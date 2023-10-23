#include <Arduino.h>

#ifndef MOTOR_H
#define MOTOR_H

#define SPEED 180
#define TURBO_SPEED 255
#define MOTOR_RIGHT_A 5
#define MOTOR_RIGHT_B 3
#define MOTOR_LEFT_A 11
#define MOTOR_LEFT_B 6

class Motor {
    private:
        bool invertControllsFlag = false;
    public:
        Motor ();
        void fleft (uint8_t speed, bool direction);
        void fright (uint8_t speed, bool direction);

        void left (uint8_t speed);
        void right (uint8_t speed);
        void forward (uint8_t speed);
        void backward (uint8_t speed);
        void stop ();
        void joystick (uint8_t joystick, bool turbo);
        void invertControlls ();
};

#endif