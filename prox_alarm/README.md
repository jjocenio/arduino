## Proximity Alarm

This is a small project to show how to use the Arduino Uno R3 and the ultrasonic sensor to build an alarm based on the distance from the sensor.

The project used the following components:

- 01 x One R3
- 01 x Ultrasonic Sensor HC-SR04
- 06 x 5mm led (2 red, 2 yellow, 2 green)
- 06 x 220 ohm resistor
- 01 x Passive buzzer
- 06 x F-M wires
- 13 x M-M wires

It works like this:

- If the distance is between 60 and 75cm, turn one green on and beep once per second
- If the distance is between 45 and 60cm, turn all green and one yellow on and beep 3 times per second
- If the distance is between 30 and 45cm, turn all green and all yellow on and beep 5 times per second
- If the distance is between 10 and 20cm, turn all green, all yellow and one red on and beep 7 times per second
- If the distance is up to 10cm, turn all LEDs on and beep like a crazy

Here is the breadbord shema.

![breadboard schema](https://raw.githubusercontent.com/jjocenio/arduino/master/prox_alarm/prox_alarm_bb.jpg)

Click in the followin picture to watch the video.

[![Watch the video](https://raw.githubusercontent.com/jjocenio/arduino/master/prox_alarm/picture.jpg)](https://youtu.be/APMYM2LCBTI)