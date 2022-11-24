# OpenSource Smartglass Project
---

##PCB Versions:

### Version 0.5

Production: JLCPCB, 4 layer, blue
Date: TBD

- see if the BQ25887 a 4mm2 24pin 2S charger with built in balancer is avalable
- addin i2S audio amplifier, or a piezo MEMS speaker


### Version 0.4a

Production: JLCPCB, 4 layer, blue
Date: TBD

- change backside font from 0.07mm thick to a 0.11mm thickness
- change R15 and R16 from 10K to 4.7K on schematic (i2C pullup resistor values could go down to 2.7K if needed)
- added Left/Right text to Microphone selection on schematic
- add a pin 1 Dot to IC's
- moved User switch 0.35mm up and a bit to the front edge of PCB
- moved R8 text to board edge
- decreased C14 font size


### Version 0.4

Production: JLCPCB, 4 layer, green
Date: 2022-09-22

- fix ESP32-Pico 3.3VA to 3.3V missing connection
- swap out external PDM microphone for SPH0645/ICS-43434 i2S microphone footprint.  Keep onboard PDM microphone
- addin breakout for extra i2S microphone channel
- addin on/off switch, via MOSFET control, or EN pin on a LDO
- addin provision for a RGB LEDs on reverse side of board
- swap out TP4056 for a AP5054 SOT23-5 battery charger
- add a SY7088 3V to 5V boost DC-DC converter
- add in MAX17048 i2C based Fuel Gauge IC
- add on a touch senser breakout connector pads


### Version 0.3

Production: JLCPCB, 4 layer, green
Date: 2022 August 

- ESP32-Pico-D4 MCU
- PDM over i2S microphones
- TP4056 battery charger

