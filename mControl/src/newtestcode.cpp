#include <Arduino.h>

const int rotateDirPin = 3;
const int rotateStepPin = 2;

const int linearDirPin = 5;
const int linearStepPin = 4;

const int stepsPerRevolution = 200;  // Adjust for your motor's steps per revolution

void setup() {
  pinMode(rotateStepPin, OUTPUT);
  pinMode(rotateDirPin, OUTPUT);
  pinMode(linearStepPin, OUTPUT);
  pinMode(linearDirPin, OUTPUT);
  Serial.begin(9600);
}

void moveStepperRotate(int steps, int direction, int initialDelayMicros, int stepPin, int dirPin) {
  digitalWrite(dirPin, direction);

  int currentDelayMicros = initialDelayMicros;

  for (int x = 0; x < steps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(currentDelayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(currentDelayMicros);

    if (currentDelayMicros > 500) {
      currentDelayMicros -= 10;
    }
  }
}

void moveStepperLinear(int steps, int direction, int initialDelayMicros, int stepPin, int dirPin) {
  digitalWrite(dirPin, direction);

  int currentDelayMicros = initialDelayMicros;

  for (int x = 0; x < steps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(currentDelayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(currentDelayMicros);

    if (currentDelayMicros > 500) {
      currentDelayMicros -= 10;
    }
  }
}

void loop() {
  // Rotate Motor Parameters
  int rotateSteps = 400;  // Adjust the number of steps for rotation
  int rotateInitialDelayMicros = 1000;  // Adjust the initial delay for rotation
  int rotateDuration = 15000;  // 15 seconds duration for rotation

  // Linear Motor Parameters
  int linearSteps = 20 * stepsPerRevolution;  // 20 rounds for linear motion
  int linearInitialDelayMicros = 1000;  // Adjust the initial delay for linear motion
  int linearDuration = 20000;  // 20 seconds duration for linear motion

  // Rotate Motor for 15 seconds
  unsigned long rotateStartTime = millis();
  while (millis() - rotateStartTime < rotateDuration) {
    moveStepperRotate(rotateSteps, LOW, rotateInitialDelayMicros, rotateStepPin, rotateDirPin);
  }

  // Linear Motor for 20 seconds
  unsigned long linearStartTime = millis();
  while (millis() - linearStartTime < linearDuration) {
    moveStepperLinear(linearSteps, LOW, linearInitialDelayMicros, linearStepPin, linearDirPin);
  }

  // Stop both motors
  digitalWrite(rotateStepPin, LOW);
  digitalWrite(linearStepPin, LOW);

  // Introduce a delay before the next iteration
  delay(2000);
}
