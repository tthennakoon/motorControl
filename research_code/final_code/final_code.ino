#include <Arduino.h>
#include <AccelStepper.h>

const int dirPin = 2;
const int stepPin = 3;
const int lmswitch1 = 6;
const int lmswitch2 = 7;

const int stepsPerRevolution = 200;  // Adjust for your motor's steps per revolution

AccelStepper stepper1(AccelStepper::FULL4WIRE, 2, 3, 4, 5);
AccelStepper stepper2(AccelStepper::FULL4WIRE, 8, 9, 10, 11);

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(lmswitch1, INPUT_PULLUP);
  pinMode(lmswitch2, INPUT_PULLUP);
  Serial.begin(9600);
}

void moveStepper(int steps, int direction, int delayMicros, AccelStepper &stepper) {
  digitalWrite(dirPin, direction);
  for (int x = 0; x < steps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayMicros);
  }
}

void homeStepper() {
  // Homing Sequence
  while (digitalRead(lmswitch1) == HIGH && digitalRead(lmswitch2) == HIGH) {
    moveStepper(1, LOW, 1000, stepper1);  // Move one step at a time until either lmswitch1 or lmswitch2 is triggered
  }

  // Determine which limit switch is triggered
  if (digitalRead(lmswitch1) == LOW) {
    // lmswitch1 is triggered
    moveStepper(50, HIGH, 1000, stepper1);  // Move the stepper a bit in the opposite direction
  } else {
    // lmswitch2 is triggered
    // Adjust as needed for your specific homing sequence
  }

  // Continue with the rest of the homing sequence or other actions
}

void loop() {
  homeStepper();

  if (Serial.available() > 0) {
    // Read the incoming data as a string
    String input = Serial.readStringUntil('\n');

    // Parse the input string to get motor positions in degrees
    float degrees1 = input.substring(0, input.indexOf(',')).toFloat();
    float degrees2 = input.substring(input.indexOf(',') + 1).toFloat();

    // Convert degrees to steps
    int steps1 = degreesToSteps(degrees1);
    int steps2 = degreesToSteps(degrees2);

    // Move the motors to the specified positions
    moveMotor(stepper1, steps1);
    moveMotor(stepper2, steps2);
  }
}

void moveMotor(AccelStepper &stepper, int targetSteps) {
  // Set the target position
  stepper.moveTo(targetSteps);

  // Move the motor until it reaches the target position
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

int degreesToSteps(float degrees) {
  // Convert degrees to steps based on steps per revolution
  return degrees * stepsPerRevolution / 360;
}
