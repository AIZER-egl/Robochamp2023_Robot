#include "motor.h"


Motor::Motor () {
}

void Motor::fleft (uint8_t speed, bool direction) {
    direction = invertControllsFlag ? !direction : direction;
    if (direction) {
        analogWrite(MOTOR_LEFT_A, speed);
        analogWrite(MOTOR_LEFT_B, 0);
    } else {
        analogWrite(MOTOR_LEFT_A, 0);
        analogWrite(MOTOR_LEFT_B, speed);
    }
}

void Motor::fright (uint8_t speed, bool direction) {
    direction = invertControllsFlag ? !direction : direction;
    if (direction) {
        analogWrite(MOTOR_RIGHT_A, speed);
        analogWrite(MOTOR_RIGHT_B, 0);
    } else {
        analogWrite(MOTOR_RIGHT_A, 0);
        analogWrite(MOTOR_RIGHT_B, speed);
    }
}

void Motor::left (uint8_t speed) {
    fleft(speed, 0);
    fright(speed, 1);
}

void Motor::right (uint8_t speed) {
    fleft(speed, 1);
    fright(speed, 0);
}

void Motor::forward (uint8_t speed) {
    fleft(speed, 1);
    fright(speed, 1);
}

void Motor::backward (uint8_t speed) {
    fleft(speed, 0);
    fright(speed, 0);
}

void Motor::stop () {
    fleft(0, 0);
    fright(0, 0);
}

void Motor::invertControlls () {
    invertControllsFlag = !invertControllsFlag;
}

void Motor::joystick(uint8_t joystick, bool turbo) {
  switch (joystick) {
  case 1:
    stop();
    break;
  case 2:
    forward(turbo ? TURBO_SPEED : SPEED);
    break;
  case 3:
    backward(turbo ? TURBO_SPEED : SPEED);
    break;
  case 4:
    right(turbo ? (TURBO_SPEED / 2) : (SPEED / 2));
    break;
  case 5:
    right(turbo ? (TURBO_SPEED / 3) : (SPEED / 3));
    break;
  case 6:
    right(turbo ? TURBO_SPEED : SPEED);
    break;
  case 7:
    left(turbo ? (TURBO_SPEED / 2) : (SPEED / 2));
    break;
  case 8:
    left(turbo ? (TURBO_SPEED / 3) : (SPEED / 3));
    break;
  case 9:
    left(turbo ? TURBO_SPEED : SPEED);
    break;
  default:
    stop();
    break;
  }
}