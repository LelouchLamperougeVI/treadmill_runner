#ifndef LICKSENSE_H
#define LICKSENSE_H

#include "Arduino.h"

namespace LS {
  // Constant parameters
  const int si = 10; // sampling interval in ms
  const int cl_max = 16000; // maximum wait cycles for resistor pull down
  const int thres = 1000; // threshold for lick triggering
  const int pulseWidth = 20; // length of forwarding pulse

  // Sensor class
  class lickSense {
    private:
      int pinS, pin5, pinF; // sensor, 5 volt and forwarding pins respectively
      unsigned long t0 = 0;
      unsigned long fwd_t = 0xffffffff;
      unsigned long t;
      bool preLick = false;
      
      volatile uint8_t* port;
      volatile uint8_t* ddr;
      volatile uint8_t* pinr;
      byte mask;
      
      int capSense();
      
    public:
      int val;
      bool isLick = false;
      
      lickSense(int S, int V, int F);
      void loop();
  };
}

#endif
