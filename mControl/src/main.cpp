#include <Arduino.h>

const int dirPin = 3;
const int stepPin = 2;

const int stepsPerRevolution = 200; // Adjust for your motor's steps per revolution

void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600);
}

//void limiting

//void splitfuc():


void moveStepper(int steps, int direction, int initialDelayMicros)
{
  digitalWrite(dirPin, direction);

  int currentDelayMicros = initialDelayMicros;

  for (int x = 0; x < steps; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(currentDelayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(currentDelayMicros);

    // Gradually decrease delay for smoother acceleration
    if (currentDelayMicros > 500)
    {
      currentDelayMicros -= 10;
    }
  }
}

void loop()
{
  // Adjust the speed and number of rounds as needed
  int desiredSpeed = 20;  // Adjust the desired speed in steps per second
  int numberOfRounds = 5; // Adjust the number of rounds to move the motor
  bool Direction = true;

  int stepsToMove = numberOfRounds * stepsPerRevolution;
  int initialDelayMicros = 1000; // Adjust the initial delay as needed

  // Move the stepper motor with specified speed and number of rounds
  moveStepper(stepsToMove, Direction ? HIGH : LOW, initialDelayMicros);

  Direction = !Direction;

  // Stop the motor
  digitalWrite(stepPin, LOW);
  delay(2500); // Adjust the delay as needed
}