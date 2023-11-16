#include <Arduino.h>

const int rotateDirPin = 3;
const int rotateStepPin = 2;

const int linearDirPin = 5;
const int linearStepPin = 4;

const int stepsPerRevolutionRotation = 800; // Adjust for your motor's steps per revolution
const int stepsPerRevolutionLinear = 1600;  // Adjust for your motor's steps per revolution

void setup()
{
  pinMode(rotateStepPin, OUTPUT);
  pinMode(rotateDirPin, OUTPUT);
  pinMode(linearStepPin, OUTPUT);
  pinMode(linearDirPin, OUTPUT);

  Serial.begin(9600);
}

void moveStepper(int steps, int dir, int initialDelayMicros, int stepPin, int dirPin)
{
  digitalWrite(dirPin, dir);

  for (int i = 0; i < steps; i++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(initialDelayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(initialDelayMicros);
  }
}

void moveStepperMotor(int steps, int initialDelayMicros, int duration, int stepPin, int dirPin)
{
  unsigned long startTime = millis();
  while (millis() - startTime < (unsigned long)duration)
  {
    moveStepper(steps, LOW, initialDelayMicros, stepPin, dirPin);
  }
  digitalWrite(stepPin, LOW);
  delay(2000);
}

void loop()
{
  // Rotate Motor Parameters
  int rotationRotate = 3;
  int rotateSteps = rotationRotate * stepsPerRevolutionRotation; // Adjust the number of steps for rotation
  int rotateInitialDelayMicros = 1000;                           // Adjust the initial delay for rotation
  int rotateDuration = 5000;

  // Linear Motor Parameters
  int rotationLinear = 3;
  int linearSteps = rotationLinear * stepsPerRevolutionLinear; // 20 rounds for linear motion
  int linearInitialDelayMicros = 1000;                         // Adjust the initial delay for linear motion
  int linearDuration = 5000;

  moveStepperMotor(rotateSteps, rotateInitialDelayMicros, rotateDuration, rotateStepPin, rotateDirPin);
  moveStepperMotor(linearSteps, linearInitialDelayMicros, linearDuration, linearStepPin, linearDirPin);

  // Rotate Motor for 15 seconds
  // unsigned long rotateStartTime = millis();
  // while (millis() - rotateStartTime < (unsigned long)rotateDuration)
  // {
  // moveStepperMotor(rotateSteps, rotateInitialDelayMicros, rotateDuration, rotateStepPin, rotateDirPin);
  // }

  // Linear Motor for 20 seconds
  // unsigned long linearStartTime = millis();
  // while (millis() - linearStartTime < (unsigned long)linearDuration)
  // {
  // moveStepperMotor(linearSteps, linearInitialDelayMicros, linearDuration, linearStepPin, linearDirPin);
  // }

  // Stop both motors
  digitalWrite(rotateStepPin, LOW);
  digitalWrite(linearStepPin, LOW);

  // Introduce a delay before the next iteration
  delay(2000);
}
