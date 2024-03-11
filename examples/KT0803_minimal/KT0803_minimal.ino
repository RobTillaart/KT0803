//
//    FILE: KT0803_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/KT0803


#include "Arduino.h"
#include "Wire.h"
#include "KT0803.h"


KT0803 FM_SEND;


void setup()
{
  Serial.begin(115200);
  while(!Serial);

  Wire.begin();
  
  FM_SEND.begin();
  FM_SEND.setChannel(1000);  //  100.0 MHz
  FM_SEND.setMute(false);
}

void loop()
{
}


//  -- END OF FILE --
