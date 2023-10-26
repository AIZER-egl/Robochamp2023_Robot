#include "thrower.h"

Thrower::Thrower () {
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
}

void Thrower::shoot () {
    digitalWrite(MOTOR_A, HIGH);
    digitalWrite(MOTOR_B, LOW);
}

void Thrower::stop () {
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, LOW);
}