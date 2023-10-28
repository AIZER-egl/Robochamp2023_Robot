#include "thrower.h"

Thrower::Thrower () {
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
}

void Thrower::shoot () {
    servo.attach(SERVO_DOOR);

    digitalWrite(MOTOR_A, HIGH);
    digitalWrite(MOTOR_B, LOW);
    delay(1500);

    servo.write(100);
    delay(1000);

    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, LOW);
 
    servo.write(180);
    delay(1000);
    servo.detach();

    Serial.read(); // Clear serial buffer
}

void Thrower::stop () {
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, LOW);
}