#include <Arduino.h>

// Define constants for pin numbers
const int dirPinRotatable = 3;  // Direction pin for Rotatable Motor
const int stepPinRotatable = 2; // Step pin for Rotatable Motor

const int dirPinLinear = 5;  // Direction pin for Linear Motor
const int stepPinLinear = 4; // Step pin for Linear Motor

#define STEPS_PER_REVOLUTION 800 // Number of steps per revolution for both motors

// Setup function to initialize pins and serial communication
void setup()
{
  pinMode(stepPinRotatable, OUTPUT); // Set Rotatable Motor step pin as output
  pinMode(dirPinRotatable, OUTPUT);  // Set Rotatable Motor direction pin as output
  pinMode(dirPinLinear, OUTPUT);     // Set Linear Motor direction pin as output
  pinMode(stepPinLinear, OUTPUT);    // Set Linear Motor step pin as output

  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

// Function to move a stepper motor
void moveStepperMotor(int steps, int direction, int initialDelayMicros, int stepPin, int dirPin)
{
  digitalWrite(dirPin, direction); // Set the direction of the motor

  int currentDelayMicros = initialDelayMicros; // Set the initial delay between steps

  // Move the motor for the specified number of steps
  for (int x = 0; x < steps; x++)
  {
    digitalWrite(stepPin, HIGH);           // Energize the step pin
    delayMicroseconds(currentDelayMicros); // Delay for the specified time

    digitalWrite(stepPin, LOW);            // De-energize the step pin
    delayMicroseconds(currentDelayMicros); // Delay for the specified time

    // Gradually reduce the delay between steps if it exceeds 500 microseconds
    if (currentDelayMicros > 500)
    {
      currentDelayMicros -= 5;
    }
  }
}

// Function to calculate the number of steps for a given number of rotations
int calculateSteps(int rotations)
{
  return rotations * STEPS_PER_REVOLUTION; // Multiply rotations by steps per revolution
}

// Function to perform the rotation sequence for both motors
void performRotationSequence()
{
  // Rotatable Motor Parameters
  int rotationRotatable = 10;                             // Set the number of rotations for the Rotatable Motor
  int stepsRotatable = calculateSteps(rotationRotatable); // Calculate the number of steps for 10 rotations
  int initialDelayMicrosRotatable = 1000;                 // Set the initial delay for the Rotatable Motor

  // Linear Motor Parameters
  int rotationLinear = 10;                          // Set the number of rotations for the Linear Motor
  int stepsLinear = calculateSteps(rotationLinear); // Calculate the number of steps for 10 rotations
  int initialDelayMicrosLinear = 500;               // Set the initial delay for the Linear Motor

  // Move Rotatable Motor 10 rotations forward
  moveStepperMotor(stepsRotatable, LOW, initialDelayMicrosRotatable, stepPinRotatable, dirPinRotatable);

  // Move Linear Motor 1 rotation
  moveStepperMotor(stepsLinear, LOW, initialDelayMicrosLinear, stepPinLinear, dirPinLinear);

  // Move Rotatable Motor 10 rotations backward
  moveStepperMotor(stepsRotatable, HIGH, initialDelayMicrosRotatable, stepPinRotatable, dirPinRotatable);
}

// Loop function to repeat the rotation sequence 10 times
void loop()
{
  for (int i = 0; i < 10; i++)
  {                            // Repeat 10 times
    performRotationSequence(); // Perform the rotation sequence for both motors
    delay(2000);               // Delay for 2 seconds between sequences
  }
}
