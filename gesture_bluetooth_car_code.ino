/*
  Gesture & Bluetooth-Controlled Robot Car
  ------------------------------------------
  Hardware: Arduino Uno, L298N Motor Driver, 2x DC Motors,
            HC-05 Bluetooth Module, 9V Battery

  How it works:
  A paired phone/app sends single-character commands over Bluetooth
  (via gesture or voice input on the app side). The HC-05 module
  relays these over serial (RX/TX) to the Arduino, which decodes
  the command and drives the L298N motor driver using PWM for speed
  control and digital pins for direction switching.

  Command reference (adjust to match your Bluetooth app's mapping):
    'F' = Forward
    'B' = Backward
    'L' = Turn Left
    'R' = Turn Right
    'S' = Stop
    '0'-'9' = Speed level (optional, sets PWM speed)

  Wiring (adjust pins to match your actual build):
    L298N IN1 -> Pin 8   (Left motor direction 1)
    L298N IN2 -> Pin 9   (Left motor direction 2)
    L298N IN3 -> Pin 10  (Right motor direction 1)
    L298N IN4 -> Pin 11  (Right motor direction 2)
    L298N ENA -> Pin 5   (Left motor speed - PWM)
    L298N ENB -> Pin 6   (Right motor speed - PWM)
    HC-05 TXD -> Arduino RX (Pin 0) [use voltage divider if 5V logic]
    HC-05 RXD -> Arduino TX (Pin 1)
*/

// Motor direction pins
const int leftMotorPin1 = 8;
const int leftMotorPin2 = 9;
const int rightMotorPin1 = 10;
const int rightMotorPin2 = 11;

// Motor speed (PWM) pins
const int leftMotorSpeed = 5;
const int rightMotorSpeed = 6;

// Default driving speed (0-255)
int motorSpeed = 200;

char command;

void setup() {
  Serial.begin(9600);  // HC-05 default baud rate

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorSpeed, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);

  stopCar();
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char cmd) {
  switch (cmd) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':
      stopCar();
      break;
    default:
      // Optional: treat '0'-'9' as a speed level command
      if (cmd >= '0' && cmd <= '9') {
        motorSpeed = map(cmd - '0', 0, 9, 0, 255);
      }
      break;
  }
}

void moveForward() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  setSpeed(motorSpeed, motorSpeed);
}

void moveBackward() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  setSpeed(motorSpeed, motorSpeed);
}

void turnLeft() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  setSpeed(motorSpeed, motorSpeed);
}

void turnRight() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  setSpeed(motorSpeed, motorSpeed);
}

void stopCar() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
  setSpeed(0, 0);
}

void setSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(leftMotorSpeed, leftSpeed);
  analogWrite(rightMotorSpeed, rightSpeed);
}
