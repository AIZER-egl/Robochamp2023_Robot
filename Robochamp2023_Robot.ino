#include <SoftwareSerial.h>
#include "craw.h"
#include "motor.h"
#include "bitmask.h"
#include "thrower.h"

#define JOYSTICK 0
#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_C 3
#define BUTTON_D 4
#define BUTTON_E 5
#define BUTTON_F 6

Craw craw;
Motor motor;
Bitmask bitmask;
Thrower thrower;

Bitmask::BitmaskComponent bitmaskValues[7] = {
  { 0, 0x0F, 6 },
  { 0, 0x01, 5 },
  { 0, 0x01, 4 },
  { 0, 0x01, 3 },
  { 0, 0x01, 2 },
  { 0, 0x01, 1 },
  { 0, 0x01, 0 },
};

Bitmask::BitmaskComponent * bitmaskValuesPointer = bitmaskValues;
bool previousInvertControlls = false;
void setup () {
  Serial.begin(38400);
  Serial.println("Program started");
  stopExcecution();
}

void loop () {
  if (Serial.available()) {
    String read = Serial.readStringUntil('\n');
    int bitmaskReceived = read.toInt();
    int joystick = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, JOYSTICK);
    bool turbo = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_D);
    bool crawButton = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_A);
    bool stopButton = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_F);
    bool invertControlls = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_C);
    bool shoot = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_B);

    motor.joystick(joystick, turbo);
    if (crawButton) craw.toggle();
    if (stopButton) stopExcecution();
    if (shoot) thrower.shoot();
    else thrower.stop();  
    if (invertControlls && !previousInvertControlls) motor.invertControlls();
    previousInvertControlls = invertControlls;
  }
}

void stopExcecution () {
  motor.stop();
  for (;;) {
    if (Serial.available()) {
      String read = Serial.readStringUntil('\n');
      int bitmaskReceived = read.toInt();
      int start = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_E);
      if (start) break;
    }
  }
}
