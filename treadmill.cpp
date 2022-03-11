#include "treadmill.h"

using namespace TM;

treadmill *cptr;
static void stepperInterruptHandler() {
  cptr -> stepper();
}
static void rwdInterruptHandler() {
  cptr -> reward();
}

treadmill::treadmill(int A, int B, int rwd, int pho, int rwd_fwd, int pho_fwd) {
  pin_A = A;
  pin_B = B;
  pin_rwd = rwd;
  pin_pho = pho;
  pin_rwd_fwd = rwd_fwd;
  pin_pho_fwd = pho_fwd;

  cptr = this;

  attachInterrupt(digitalPinToInterrupt(pin_A), stepperInterruptHandler, CHANGE);
  pinMode(pin_B, INPUT);

  pinMode(pin_rwd, OUTPUT);
  digitalWrite(pin_rwd, LOW);
  pinMode(pin_rwd_fwd, OUTPUT);
  digitalWrite(pin_rwd_fwd, LOW);
  pinMode(pin_pho_fwd, OUTPUT);
  digitalWrite(pin_pho_fwd, LOW);

  attachInterrupt(digitalPinToInterrupt(pin_pho), rwdInterruptHandler, RISING);

  reset();
  d = min_d + 1;
  reward();
  reset();
}

void treadmill::loop() {
  t = millis();
  if ((t - rwd_t) > DELAY) {
    digitalWrite(pin_rwd, LOW);
    digitalWrite(pin_rwd_fwd, LOW);
  }

  if ((t - pho_t) > DELAY) {
    digitalWrite(pin_pho_fwd, LOW);
  }

  if (d < neg_d)
    reset();

  delay(1);
}

void treadmill::stepper() {
  A = digitalRead(pin_A);
  B = digitalRead(pin_B);
  A == B ? steps++ : steps--;
  d = (float) steps / enc_pls * 2.0 * PI * rad;
}

void treadmill::reward() {
  digitalWrite(pin_pho_fwd, HIGH);
  pho_t = millis();
  
  if (d > min_d) {
    digitalWrite(pin_rwd, HIGH);
    digitalWrite(pin_rwd_fwd, HIGH);
    rwd_t = millis();
    Serial.print("lap no. ");
    Serial.print(laps);
    Serial.print("\n");
    Serial.print("dist. ");
    Serial.print(d);
    Serial.print("\n");
    reset();
    laps++;
  }
}

void treadmill::reset() {
  d = 0.0;
  steps = 0;
}
