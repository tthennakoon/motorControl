#include <Arduino.h>

const int stepPinRotatable = 2;
const int dirPinRotatable = 3;

const int stepPinLinear = 4;
const int dirPinLinear = 5;

bool isOnline = false;

#define STEPS_PER_REVOLUTION 800

void moveRotatableMotor(int steps, int direction)
{
    int initialDelayMicrosRotatable = 600;
    digitalWrite(dirPinRotatable, direction);
    int currentDelayMicros = initialDelayMicrosRotatable;

    for (int x = 0; x < steps; x++)
    {
        digitalWrite(stepPinRotatable, HIGH);
        delayMicroseconds(currentDelayMicros);
        digitalWrite(stepPinRotatable, LOW);
        delayMicroseconds(currentDelayMicros);
    }
}

void moveLinearMotor(int steps, int direction)
{
    int currentDelayMicros = 100;
    digitalWrite(dirPinLinear, direction);

    for (int x = 0; x < steps; x++)
    {
        digitalWrite(stepPinLinear, HIGH);
        delayMicroseconds(currentDelayMicros);
        digitalWrite(stepPinLinear, LOW);
        delayMicroseconds(currentDelayMicros);
    }
}

void stop()
{
    digitalWrite(stepPinLinear, LOW);
    digitalWrite(stepPinRotatable, LOW);

    while (1)
    {
    }
}

void findHome()
{
    int limitSwitchPinLinear = 13;
    int limitSwitchPinRotary = 11;

    while (digitalRead(limitSwitchPinLinear) == LOW)
    {

        moveLinearMotor(500, LOW);
    }

    digitalWrite(stepPinLinear, LOW);

    while (digitalRead(limitSwitchPinRotary) == LOW)
    {

        moveRotatableMotor(500, HIGH);
    }
    digitalWrite(stepPinRotatable, LOW);

    delay(5000);
}

void setup()
{
    Serial.begin(9600);
    pinMode(stepPinRotatable, OUTPUT);
    pinMode(dirPinRotatable, OUTPUT);
    pinMode(dirPinLinear, OUTPUT);
    pinMode(stepPinLinear, OUTPUT);
    pinMode(11, INPUT);
    pinMode(13, INPUT);

    // findHome();
    isOnline = true;
    Serial.begin(9600);
}

bool MachineConnect()
{
    if (Serial.available() > 0)
    {
        String request = Serial.readStringUntil('\n');
        if (request == "get_status")
        {
            if (isOnline)
            {
                Serial.println("online");
                return true;
            }
            else
            {
                Serial.println("offline");
                return false;
            }
        }
    }
    return false;
}

void loop()
{
    if (Serial.available() > 0)
    {
        bool isConnected = MachineConnect();

        if (isConnected)
        {
            int directionRotatable = LOW;
            int rotationRotatable = 10000;
            int stepsRotatable = rotationRotatable * STEPS_PER_REVOLUTION;
            int stopPointsRotatable = 5;
            int stopPointsStepRotatable = stepsRotatable / stopPointsRotatable;

            for (int i = 0; i <= 2; i++)
            {
                for (int j = 0; j < stopPointsRotatable; j++)
                {
                    moveRotatableMotor(stopPointsStepRotatable, directionRotatable);
                    delay(2000);
                    Serial.print("Image captured at i = ");
                    Serial.print(i);
                    Serial.print(", j = ");
                    Serial.println(j);
                    delay(1000);
                }
                moveLinearMotor(5000, HIGH);
                delay(2000);

                directionRotatable = !directionRotatable;
            }
            // findHome();
            stop();
        }
        else
        {
            // findHome();
            stop();
        }
    }

    delay(5000);
}
