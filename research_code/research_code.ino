#include <AccelStepper.h>

// Define the stepper motor connections and steps per revolution
#define motorPin1 2
#define motorPin2 3
#define stepsPerRevolution 200  // Adjust this based on your motor specs

AccelStepper stepper1(AccelStepper::FULL4WIRE, 2, 3, 4, 5);
AccelStepper stepper2(AccelStepper::FULL4WIRE, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino is ready");
}

void loop() {
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
