#include "lickSense.h"
#include "treadmill.h"

#define pin_A 2 // encoder channel pins
#define pin_B 4
#define pin_rwd 8 // reward pin
#define pin_pho 3 // photosensor pin
#define pin_lck 40 // lick pin
#define pin_pwr 41 // the pin next to the lick pin for powering the bitch
#define pin_rwd_fwd 31 //reward forwarding pin
#define pin_pho_fwd 24 // photosensor forwarding pin
#define pin_lck_fwd 24 // licking forwarding pin

LS::lickSense licker(pin_lck, pin_pwr, pin_lck_fwd);
TM::treadmill tobj(pin_A, pin_B, pin_rwd, pin_pho, pin_rwd_fwd, pin_pho_fwd);
unsigned long timer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("lap no. ");
}

void loop() {
  // put your main code here, to run repeatedly:
  licker.loop();
  tobj.loop();
  if ((millis() - timer) > 10)
    digitalWrite(LED_BUILTIN, LOW);
  if (licker.isLick) {
    digitalWrite(LED_BUILTIN, HIGH);
    timer = millis();
  }
}
