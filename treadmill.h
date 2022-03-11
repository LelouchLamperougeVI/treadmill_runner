#ifndef TREADMILL_H
#define TREADMILL_H

#include "Arduino.h"

namespace TM {
  // Constant parameters
  const float enc_pls = 1000.0; //number of pulses per revolution of encoder
  const float rad = 5.0; //radius of wheel
  const int DELAY = 30; //reward valve open time in ms
  const float min_d = 30.0; // minimum distance traveled for reward to avoid cheating
  const float neg_d = -30.0; // resetting distance

  // Treadmill class
  class treadmill {
    private:
      int pin_A, pin_B, pin_rwd, pin_pho, pin_rwd_fwd, pin_pho_fwd;
      unsigned long rwd_t = 0xffffffff;
      unsigned long pho_t = 0xffffffff;
      unsigned long t;
      bool A, B;
      
      void reset();
      
    public:
      int laps = 0;
      int steps;
      float d;

      treadmill(int A, int B, int rwd, int pho, int rwd_fwd, int pho_fwd);
      void loop();
      void stepper();
      void reward();
  };
}

#endif
