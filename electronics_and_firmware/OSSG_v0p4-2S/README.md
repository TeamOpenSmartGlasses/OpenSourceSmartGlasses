# Open Source Smartglasses PCB V0.4
---

This version was an attempt to use a 2S battery pack.  The main issue is that as of 2022-09-15, there are not many 2S battery charging IC's nor a nice i2C fuel gauge IC, so at the moment, this is a dead end design.

### Features:

- i2S microphones (non PDM)
- 2S battery configuration
- 2S battery charger
- on/off switch
- auto switch off when one battery goes below 2.7V
- the design is missing the 5V to 12V at 1.5A boost circuit that could be based around a SY7088 IC

