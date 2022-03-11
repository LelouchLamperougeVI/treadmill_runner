#include "lickSense.h"

using namespace LS;

lickSense::lickSense (int S, int V, int F) {
  pinS = S;
  pin5 = V;
  pinF = F;
  mask = digital_pin_to_bit_mask_PGM[pinS];
  
  uint8_t phys_port = digital_pin_to_port_PGM[pinS];
  port = port_to_output_PGM[phys_port];
  ddr = port_to_mode_PGM[phys_port];
  pinr = port_to_input_PGM[phys_port];

  pinMode(pin5, OUTPUT);
  digitalWrite(pin5, HIGH);
  pinMode(pinF, OUTPUT);
  digitalWrite(pinF, LOW);
}

void lickSense::loop () {
  t = millis();
  if ((t - t0) > si) {
    val = capSense();
    
    isLick = !preLick & (val > thres);
    preLick = val > thres;
    if (isLick) {
      digitalWrite(pinF, HIGH);
      fwd_t = t;
    }
    
    t0 = t;
  }
  if ((t - fwd_t) > pulseWidth) {
    digitalWrite(pinF, LOW);
  }
}

int lickSense::capSense () {
  *port &= ~(mask);
  *ddr |= mask;
  delay(1);

  *ddr &= ~(mask);

  int cycles = 0;
  for (; cycles < cl_max; cycles++) {
    if (*pinr & mask) {
      break;
    }
  }

  *port &= ~(mask);
  *ddr |= mask;

  return cycles;
}
