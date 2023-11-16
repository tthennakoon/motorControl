#include <Arduino.h>

const int dirPinRotatable = 3;
const int stepPinRotatable = 2;

const int dirPinLinear = 5;
const int stepPinLinear = 4;

#define STEPS_PER_REVOLUTION 800

void setup()
{
  pinMode(stepPinRotatable, OUTPUT);
  pinMode(dirPinRotatable, OUTPUT);
  pinMode(dirPinLinear, OUTPUT);
  pinMode(stepPinLinear, OUTPUT);

  Serial.begin(9600);
}

void moveStepperMotor(int steps, int direction, int initialDelayMicros, int stepPin, int dirPin)
{
  digitalWrite(dirPin, direction);

  int currentDelayMicros = initialDelayMicros;
  for (int x = 0; x < steps; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(currentDelayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(currentDelayMicros);

    if (currentDelayMicros > 500)
    {
      currentDelayMicros -= 5;
    }
  }
}

int calculateSteps(int rotations)
{
  return rotations * STEPS_PER_REVOLUTION;
}

void loop()
{
  // Rotatable Motor Parameters
  int directionRotatable = LOW;
  int rotationRotatable = 20;
  int stepsRotatable = calculateSteps(rotationRotatable);
  int stopPointsRotatable = 6;
  int initialDelayMicrosRotatable = 1000;

  // Linear Motor Parameters
  int rotationLinear = 10;
  int stepsLinear = calculateSteps(rotationLinear);
  int stopPointsLinear = 10;
  int stopPointsStepLinear = stepsLinear / stopPointsLinear;
  int initialDelayMicrosLinear = 500;

  // Repeat the sequence according to stopPointsLinear
  for (int i = 0; i < stopPointsLinear; i++)
  {
    // Move Rotatable Motor according to stopPointsRotatable
    for (int i = 0; i < stopPointsRotatable; i++)
    {
      moveStepperMotor(stepsRotatable, directionRotatable, initialDelayMicrosRotatable, stepPinRotatable, dirPinRotatable);
    }
    // Move Rotatable Motor one step
    moveStepperMotor(stopPointsStepLinear, LOW, initialDelayMicrosLinear, stepPinLinear, dirPinLinear);

    directionRotatable = !directionRotatable;
  }

  digitalWrite(stepPinRotatable, LOW);
  digitalWrite(stepPinLinear, LOW);

  delay(2000);
}