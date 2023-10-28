#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include "craw.h"
#include "motor.h"
#include "bitmask.h"
#include "thrower.h"

#define TIME_BLUETOOTH_INACTIVE 1000
#define JOYSTICK 0
#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_C 3
#define BUTTON_D 4
#define BUTTON_E 5
#define BUTTON_F 6

LiquidCrystal_I2C lcd(0x27, 16, 2);
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
uint32_t timeSinceDataReceived = 0;
char lcdContent[64];

void setup () {
  Serial.begin(38400);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PREPATEC AIZER");
  lcd.setCursor(0, 1);
  lcd.print("  ROBOCHAMP 2023");
  stopExcecution();
}

void loop () {
  if (Serial.available()) {
    timeSinceDataReceived = millis();
    String read = Serial.readStringUntil('\n');
    sprintf(lcdContent, "BT: %s", read.c_str());
    lcd.setCursor(0, 1);
    lcd.print(lcdContent);

    int bitmaskReceived = read.toInt();
    int joystick = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, JOYSTICK);
    bool turbo = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_D);
    bool crawButton = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_A);
    bool stopButton = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_F);
    bool invertControlls = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_C);
    bool shoot = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_B);

    motor.joystick(joystick, turbo);
    if (crawButton && joystick == 1) craw.toggle();
    if (stopButton) stopExcecution();
    if (shoot) thrower.shoot();
    if (invertControlls && !previousInvertControlls) motor.invertControlls();
    previousInvertControlls = invertControlls;
  }

  // if (timeSinceDataReceived + TIME_BLUETOOTH_INACTIVE <= millis()) stopExcecution();
}

void stopExcecution () {
  motor.stop();
  thrower.stop();
  lcd.setCursor(0, 1);
  lcd.print("  ROBOCHAMP 2023");
  for (;;) {
    if (Serial.available()) {
      String read = Serial.readStringUntil('\n');
      int bitmaskReceived = read.toInt();
      int start = bitmask.bitmaskToValue(bitmaskReceived, bitmaskValuesPointer, BUTTON_E);
      if (start) break;
    }
  }
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
