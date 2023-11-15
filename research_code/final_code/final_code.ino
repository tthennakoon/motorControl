#include <Arduino.h>

const int dirPin1 = 2;
const int stepPin1 = 3;
const int enablePin1 = 4;  // Connect to the ENA+ and ENA- pins on the TB6600

const int dirPin2 = 8;
const int stepPin2 = 9;
const int enablePin2 = 10;  // Connect to the ENB+ and ENB- pins on the TB6600

const int lmswitch1 = 6;
const int lmswitch2 = 7;

const int stepsPerRevolution = 200;  // Adjust for your motor's steps per revolution

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(enablePin1, OUTPUT);  // Set the enable pin as OUTPUT
  pinMode(lmswitch1, INPUT_PULLUP);

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);  // Set the enable pin as OUTPUT
  pinMode(lmswitch2, INPUT_PULLUP);

  digitalWrite(enablePin1, LOW);  // Enable the motor driver
  digitalWrite(enablePin2, LOW);  // Enable the motor driver

  Serial.begin(9600);
}

void moveStepper(int steps, int direction, int delayMicros, int stepPin, int dirPin) {
  digitalWrite(dirPin, direction);
  for (int x = 0; x < steps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayMicros);
  }
}

void homeStepper(int stepPin, int dirPin, int lmswitch) {
  // Homing Sequence
  while (digitalRead(lmswitch) == HIGH) {
    moveStepper(1, LOW, 1000, stepPin, dirPin);
  }
  
  moveStepper(50, HIGH, 1000, stepPin, dirPin);
}

void loop() {
  homeStepper(stepPin1, dirPin1, lmswitch1);
  homeStepper(stepPin2, dirPin2, lmswitch2);

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    float degrees1 = input.substring(0, input.indexOf(',')).toFloat();
    float degrees2 = input.substring(input.indexOf(',') + 1).toFloat();
    int steps1 = degreesToSteps(degrees1);
    int steps2 = degreesToSteps(degrees2);

    moveMotor(steps1, stepPin1, dirPin1);
    moveMotor(steps2, stepPin2, dirPin2);
  }
}

void moveMotor(int targetSteps, int stepPin, int dirPin) {
  digitalWrite(dirPin, (targetSteps >= 0) ? HIGH : LOW);
  targetSteps = abs(targetSteps);

  for (int i = 0; i < targetSteps; ++i) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

int degreesToSteps(float degrees) {
  return degrees * stepsPerRevolution / 360;
}
