# LED strip controlled by Arduino and IR remote

With a WS2811 LED strip, you can control any LED on the strip and manage RGB or HSV (Hue-Saturation-Value) parameters with a Nano's ATM328. Inputs can be read from a standard 38kHz IR remote control. This setup can be very convenient for instance in a car to light up an area surrounded by darkness, aka the rear seats.

## Requirements

1. Arduino ATM 328P or clone _slow but cheap_
2. WS2811 LED strip _cheap_
3. IR sensor (like TOP4838) with any standard remote control _I used the one packed with a commercial LED bulb_
4. SPST switch
5. LM2596 voltage regulator for the MCU power supply _or any voltage reg. that fits the 12V -> 5V_
6. 2A fuse and holder _2A fuse is enough for approx. a 1.5m long strip_

## Setup

You must find a 12V output wire somewhere in the car in order to power supply the whole thing. As the wire is constantly powered, I used a small switch that disconnect the MCU and the LED strip.

Install the strip where you need, and bring 3 wires (AWG 22-28 is fine) to it from the place where the main unit will stand.

There are two modes of control : via the IR remote control or with a couple of buttons. The buttons are in a pull-up configuration.

![pictures](docs/LED%20strip%20IR%20controlled%20_bb.png)

## Program

I used 2 libraries :

- _IRremote_ to receive and use data from the IR sensor
- _FastLED_ to control each of the LED in the strip

The arduino Nano isn't fast enough to handle interrupts when _FastLED_ is working with the strip. [Marc Merlin explained that in his very nice LED pants and shirt project](http://marc.merlins.org/perso/arduino/post_2017-04-03_Arduino-328P-Uno-Teensy3_1-ESP8266-ESP32-IR-and-Neopixels.html#IRneopixels) or directly in [the FastLED documentation](https://github.com/FastLED/FastLED/wiki/Interrupt-problems)

It doesn't really bother me as the primary goal of this setup is to lite on some or all the LEDs. LEDs animation is a bonus, and have a limited duration. Once finished, the remote control will be functional again.

For each LED, there is a boolean activated state. These values are read each time there is a change from the inputs.

The loop section is just a long series of switch case blocks for each IR received message. To control with buttons, 

## Conclusion

I should have set up a voltage regulator at first place, because over tension had fried a nano card.
Otherwise, a good design for a custom box is required, to see the chip power led , to handle the switch and the buttons.

## Source & external links

[Engineers Garage](https://www.engineersgarage.com/how-to-build-an-ir-remote-operated-rgb-led-strip-using-arduino/)

[WS2811 specs - sdiplight](https://www.sdiplight.com/flexible-ws2811-led-strip/)

[IRremote lib](https://github.com/Arduino-IRremote/Arduino-IRremote)

[FastLED lib](https://github.com/FastLED/FastLED)