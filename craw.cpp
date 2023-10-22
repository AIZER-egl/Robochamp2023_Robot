#include "craw.h"

Craw::Craw() { }

void Craw::fopen() {
    servoLeft.attach(SERVO_LEFT);
    servoRight.attach(SERVO_RIGHT);

    for (int i = 0; i < (SERVO_CLOSE - SERVO_OPEN); i++) {
        servoRight.write(SERVO_OPEN + i);
        servoLeft.write(SERVO_CLOSE - i);
        delay(10);
    }

    servoRight.detach();
    servoLeft.detach();
}

void Craw::fclose() {
    servoLeft.attach(SERVO_LEFT);
    servoRight.attach(SERVO_RIGHT);

    for (int i = 0; i < (SERVO_CLOSE - SERVO_OPEN); i++) {
        servoRight.write(SERVO_CLOSE - i);
        servoLeft.write(SERVO_OPEN + i);
        delay(10);
    }

    servoRight.detach();
    servoLeft.detach();
}

void Craw::toggle () {
    if (triggeredTime == 0) {
        triggeredTime = millis();
        if (currentState) {
            fclose();
        } else {
            fopen();
        }
        currentState = !currentState;
    }
    elapsedTime = millis() - triggeredTime;
    if (elapsedTime > DELAY) {
        triggeredTime = 0;
    }
}