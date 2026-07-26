# Gesture & Bluetooth-Controlled Robot Car

Robot car controlled via gesture and voice commands, relayed over Bluetooth.

## Hardware Used
- Arduino Uno
- L298N Motor Driver
- 2× DC Motors
- HC-05 Bluetooth Module
- 9V Battery

## How It Works
Gesture and voice commands are captured on a paired device and sent over Bluetooth
to the HC-05 module. Embedded C on the Arduino handles serial parsing, PWM signal
generation, and direction switching to drive the L298N motor driver in real time.

## Tech Stack
`Arduino Uno` `Embedded C` `L298N` `HC-05` `PWM`

## What I Learned
[add your own line here — what was the trickiest part to get working]
