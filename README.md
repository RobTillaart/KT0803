
[![Arduino CI](https://github.com/RobTillaart/KT0803/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/KT0803/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/KT0803/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/KT0803/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/KT0803/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/KT0803.svg)](https://github.com/RobTillaart/KT0803/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/KT0803/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/KT0803.svg?maxAge=3600)](https://github.com/RobTillaart/KT0803/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/KT0803.svg)](https://registry.platformio.org/libraries/robtillaart/KT0803)



# KT0803

Arduino Library for KT0803 and KT0803K FM transmitter.


### Legal point of attention

In different countries there are different laws with respect to using transmitting devices 
and their range. 
Please inform yourself of the local rules and laws if and how you may or may not use a 
device like the KT0803 in your projects, either hobby, commercial or otherwise.


## Description

This **experimental** library allows basic control of the KT0803 and / or the KT0803K 
FM transmitter device.
It is primary written to understand the possibilities and the interface of the device.

The library is not tested by me with hardware yet. See future below.

There are some newer, more capable, follow up devices like model K, L and M.
From these only the KT0803K is supported since 0.2.0. 
The others are not supported (yet) although they might work as they seem backwards compatible.


#### Frequency range

The frequency range stated on the front page of the datasheet ==> 70 MHz - 108 MHz.
The frequency range stated in table 2 ==> 76 MHz - 108 MHz.
So the datasheet is at least ambiguous on this point.
Also keep in mind that the 


#### Differences

The KT0803K device has far more options, which are not implemented yet except one.
The resolution or step-size of the frequency.

|  device   |  step-size  |
|:---------:|:-----------:|
|  KT0803   |  100 KHz    |
|  KT0803K  |   50 KHz    |

According to the datasheet code for the KT0803 should work for the KT0803K.
Code with the KT0803K class will probably not work on a KT0803 (not verified).


#### Transmit frequency

The transmit frequency can be set with **setFrequency(MHz)** or by **setChannel(channel)**.
These channels differ per type device, some examples:

|  FREQUENCY   |  KT0803  |  KT0803K  |  Notes  |
|:------------:|:--------:|:---------:|:-------:|
|   70.00 MHz  |    700   |   1400    |
|   70.05 MHz  |    701   |   1401    |
|   70.10 MHz  |    701   |   1402    |
|   76.00 MHz  |    760   |   1520    |
|   80.00 MHz  |    800   |   1600    |
|   89.70 MHz  |    897   |   1794    |  default (see registers datasheet)
|  100.00 MHz  |   1000   |   2000    |
|  101.30 MHz  |   1013   |   2026    |
|  105.70 MHz  |   1057   |   2114    |
|  108.00 MHz  |   1080   |   2160    |



#### Warning

The KT0803 is an 3.3 Volt device and cannot be connected directly to 5V MCU's.


#### Related

- https://github.com/RobTillaart/KT0803
- https://www.hackster.io/hesam-moshiri/stereo-digital-fm-transmitter-circuit-arduino-code-2dbd8d
- https://www.hackster.io/hesam-moshiri/full-digital-fm-receiver-with-arduino-and-tea5767-52be37
- https://www.hackerstore.nl/Artikel/388
- https://en.wikipedia.org/wiki/FM_broadcasting


## Interface

```cpp
#include "KT0803.h"
```

#### Constructor

- **KT0803(TwoWire \*wire = &Wire)** constructor, 
optional Wire interface.
- **KT0803K(TwoWire \*wire = &Wire)** constructor, 
optional Wire interface.
- **bool begin()** initializes the library.
Furthermore it checks if the deviceAddress is available on the I2C bus.
Returns true if deviceAddress is found on the bus, false otherwise.
- **bool isConnected()** test to see if deviceAddress is found on the I2C-bus.


#### Frequency

- **bool setFrequency(float frequency)** converts the frequency in MHz to 
call **setChannel(channel)**. The value of channel is rounded off depending 
on the resolution of the device.
- **float getFrequency()** returns the current frequency, can be slightly different
from the set value due to rounding math mentioned above.
The return value is derived from a call to **getChannel()**
- **bool setChannel(uint16_t channel)** writes the channel to broadcast on to the device.
This involves two or three writes to different device registers.
- **uint16_t getChannel()** reads the selected channel from the device and 
returns it.


#### PGA, RFGain

Read Datasheet.

The KT0803K has a **PGA_LSB** (2 bits) setting, which allows setting the gain
with single (1) dB steps. This is not yet implemented in the library.

- **bool setPGA(uint8_t pga)** sets gain according to table below.
Returns false if pga is out of range (0..7).
- **uint8_t getPGA()** returns 0..7, default 0.


|  PGA  |  gain   |  notes  |
|:-----:|:-------:|:-------:|
|  111  |  12dB   |
|  110  |   8dB   |
|  101  |   4dB   |
|  100  |   0dB   |
|  000  |   0dB   |  default 
|  001  |  -4dB   |
|  010  |  -8dB   |
|  011  |  -12dB  |


#### RFGain

Read Datasheet.

Note: the RFGain value (4 bits) is distributed over three registers.
PA_BIAS (register 0x05) is only supported in the KT0803K device.
It is not yet supported in the library.

- **bool setRFGain(uint8_t rfgain)** sets rfgain according to table below.
Returns false if rfgain is out of range (0..15).
- **uint8_t getRFgain()** returns 0..15, default 15.


|  RFGAIN  |   RFout      |  PA_BIAS = 1 |  notes  |
|:--------:|:------------:|:------------:|:-------:|
|   0000   |   95.5 dBuV  |      -       |
|   0001   |   96.5 dBuV  |      -       |
|   0010   |   97.5 dBuV  |      -       |
|   0011   |   98.2 dBuV  |      -       |
|   0100   |   98.9 dBuV  |      -       |
|   0101   |  100.0 dBuV  |      -       |
|   0110   |  101.5 dBuV  |      -       |
|   0111   |  102.8 dBuV  |      -       |
|   1000   |  105.1 dBuV  |  107.2 dBuV  |
|   1001   |  105.6 dBuV  |  108.0 dBuV  |
|   1010   |  106.2 dBuV  |  108.7 dBuV  |
|   1011   |  106.5 dBuV  |  109.5 dBuV  |
|   1100   |  107.0 dBuV  |  110.3 dBuV  |
|   1101   |  107.4 dBuV  |  111.0 dBuV  |
|   1110   |  107.7 dBuV  |  111.7 dBuV  |
|   1111   |  108.0 dBuV  |  112.5 dBuV  |  default


#### Region selection

Read datasheet for details.

Note that not all frequencies are allowed in all regions / countries!

The first four are convenience wrappers for **setPHTCNST()**
If some region is missing please let me know the details and I can add 
a wrapper for it.

- **void setEurope()**
- **void setAustralia()**
- **void setUSA()**
- **void setJapan()**
- **bool setPHTCNST(bool on)** See table below.
- **bool getPHTCNST()** returns set value.

|  PHTCNST  |  time   |  Region  |
|:---------:|:-------:|:--------:|
|    0      |  75 μs  |  USA, Japan, (default)
|    1      |  50 μs  |  Europe, Australia


#### PilotToneAdjust

Read datasheet.

- **bool setPilotToneAdjust(uint8_t mode)**  HIGH = 1 LOW = 0
- **uint8_t getPilotToneAdjust()**


#### Mute

Default not muted.

- **bool setMute(bool mute)** enables or disables the transmitting
by muting the signal.
- **bool getMute()** returns the current state of muting.


## Derived classes

The KT0803L and KT0803M devices might work as they seem backwards compatible.
This needs further investigation. 


## Future

#### Must

- improve documentation
  - fill in gaps (TODO).
  - pin layout schema
- buy hardware
- test and verify.


#### Should

- check validity/range parameters
- at startup = parameters begin()
  - mute device ?
  - set 'default' frequency
- SW pin (ON/OFF) as optional parameter in constructor.
  - add functions for sw on/off, 
  - what is impact on settings? 
  - call begin () again? => default
  - explain well doc.


#### Could

- investigate support 
  - KT0803L, KT0803M (derived classes)
- examples
  - preset channels (optional EEPROM)
- investigate tea5767 FM receiver (Out of scope for this lib).
- extend settings upon request **bold** are interesting, see table

|  device   |  setting      |  register       |  Notes  |
|:---------:|:-------------:|:---------------:|:--------|
|  KT0803   |  PA_CTRL      |  13, bit 2      |  **WARNING in datasheet**
|           |               |                 |  Should it be added in API?
|  KT0803K  |  MONO/STEREO  |  04, bit 6      |  **idem**
|  KT0803K  |  PGA_LSB      |  04, bit 4+5    |  gain fine tuning -> see PGA_MOD
|  KT0803K  |  FDEV         |  04, bit 2+3    |  Frequency deviation adjustment
|  KT0803K  |  BASS         |  04, bit 0+1    |  **Bass boost control**
|  KT0803K  |  PDPA         |  0B, bit 5      |  Power Amplifier Power Down ?
|  KT0803K  |  PA_BIAS      |  0E, bit 1      |  PA bias current enhancement.
|  KT0803K  |  PW_OK  (RO)  |  0F, bit 4      |  **Power OK indicator**
|  KT0803K  |  SLNCID (RO)  |  0F, bit 2      |  1 when Silence is detected
|  KT0803K  |  LMTLVL       |  10, bit 3+4    |  **Internal audio limiter level control**
|  KT0803K  |  PGAMOD       |  10, bit 0      |  PGA mode selection  (use PGA_LSB/ not)
|  KT0803K  |  SLNCDIS      |  12, bit 7      |  Silence detection disable
|  KT0803K  |  SLNCTHL      |  12, bit 4+5+6  |  Silence detection low threshold
|  KT0803K  |  SLNCTHH      |  12, bit 1+2+3  |  Silence detection high threshold
|  KT0803K  |  SW_MOD       |  12, bit 0      |  **Switching channel mode selection**
|  KT0803K  |  SLNCTIME     |  14, bit 5+6+7  |  silence detection time
|  KT0803K  |  SLNCCNTHIGH  |  14, bit 2+3+4  |  silence detection count high
|  KT0803K  |  SLNCCNTLOW   |  15, bit 0+1+2  |  silence detection count low


#### Wont (for now)

- investigate efficiency of register access.
  - caching all (allowed) registers in **begin()**
    -  3 bytes for KT0803
    - 12 bytes for KT0803K
  - cache frequency.
  - only writing is needed. 
- send binary data over FM?
- preset frequency array in .h file (hardcoded)
- enums for parameters - readability?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

