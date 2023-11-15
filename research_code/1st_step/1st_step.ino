#include <Arduino.h>

const int PUL_PIN = 2;      // PUL-Step Pulse
const int DIR_PIN = 3;      // DIR-Direction
const int ENA_PIN = 4;      // ENA-Enable
const int LMSWITCH_PIN = 6; // Limit switch input pin

const int stepsPerRevolution = 200;  // Adjust for your motor's steps per revolution
const int stepsPerRound = stepsPerRevolution * 10;  // 10 rounds

const float pi = 3.14159265359;

void setup() {
  pinMode(PUL_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(LMSWITCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void moveStepperSmooth(int steps, int direction) {
  digitalWrite(DIR_PIN, direction);
  digitalWrite(ENA_PIN, LOW);  // Enable the motor driver

  float accelerationFactor = 0.0;

  for (int i = 0; i < steps; i++) {
    accelerationFactor = sin((i / (float)steps) * pi);
    
    digitalWrite(PUL_PIN, HIGH);
    delayMicroseconds(1000 + 1000 * accelerationFactor); // Adjust the delay based on your motor's specifications
    digitalWrite(PUL_PIN, LOW);
    delayMicroseconds(1000 + 1000 * accelerationFactor); // Adjust the delay based on your motor's specifications
  }

  digitalWrite(ENA_PIN, HIGH);  // Disable the motor driver
}

void loop() {
  // Homing Sequence
  while (digitalRead(LMSWITCH_PIN) == HIGH) {
    moveStepperSmooth(1, LOW);  // Move one step at a time until the limit switch is triggered
  }

  // At this point, the limit switch is triggered
  delay(1000);  // Wait for 1 second

  moveStepperSmooth(stepsPerRound, HIGH);  // Move the stepper in the opposite direction for 10 rounds

  // Continue with the rest of the homing sequence or other actions
}
