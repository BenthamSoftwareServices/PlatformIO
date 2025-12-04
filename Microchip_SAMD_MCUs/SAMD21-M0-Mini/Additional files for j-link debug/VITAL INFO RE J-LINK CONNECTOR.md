It is essential to remove PIN 9 from the small 10-pin male header on the SAMD21-M0-Mini module before connecting the 10-way plug from the J-LINK EDU MINI.
It can be cut off, or better pulled out whilst melting the solder on the back of the module with a soldering iron.

The reason for this is that pins 9 and 10 are connected together on the module, whereas on the j-link plug pin 9 is RESET and pin 10 is GROUND, so not removing pin 9 would cause a short circuit between RESET and GROUND.