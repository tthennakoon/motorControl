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
  int rotationRotatable = 3;
  int stepsRotatable = calculateSteps(rotationRotatable);
  int initialDelayMicrosRotatable = 1000;
  // int durationRotatable = 5000;
  bool directionRotatable = LOW;

  // Linear Motor Parameters
  int rotationLinear = 3;
  int stepsLinear = calculateSteps(rotationLinear);
  int initialDelayMicrosLinear = 1000;
  // int durationLinear = 5000;
  bool directionLinear = LOW;

  moveStepperMotor(stepsRotatable, directionRotatable, initialDelayMicrosRotatable, stepPinLinear, dirPinLinear);
  moveStepperMotor(stepsLinear, directionLinear, initialDelayMicrosLinear, stepPinRotatable, dirPinRotatable);

  digitalWrite(stepPinRotatable, LOW);
  digitalWrite(stepPinLinear, LOW);

  delay(2000);
}
