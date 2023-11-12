// Model,  Holding Torque, Rated voltage,  Shaft,  Step angle, Motor length, Rated current,  Inductance
// 2SHDC3025-24B  40 N·cm,  3.96 V, Ø 5 mm Single,  1.8°, 40 mm,  0.9A
#include <Arduino.h>
const int dirPin = 2;
const int stepPin = 3;
const int lmswitch1 = 6;

const int stepsPerRevolution = 200;  // Adjust for your motor's steps per revolution

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(lmswitch1, INPUT_PULLUP);
  Serial.begin(9600);
}

void moveStepper(int steps, int direction, int delayMicros) {
  digitalWrite(dirPin, direction);
  for (int x = 0; x < steps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayMicros);
  }
}

void loop() {
  // Homing Sequence
  while (digitalRead(lmswitch1) == HIGH) {
    moveStepper(1, LOW, 1000);  // Move one step at a time until lmswitch1 is triggered
  }
  // At this point, lmswitch1 is triggered
  moveStepper(50, HIGH, 1000);  // Move the stepper a bit in the opposite direction
  // Continue with the rest of the homing sequence or other actions
}
