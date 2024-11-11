#include <Arduino.h>

// IR sensor pins
int IRSensors[] = {0, 1};

// Motor pins
int Motors[] = {2, 3, 4, 5};

// Debouncing variables
int leftIRValuePrevious = 0;
int rightIRValuePrevious = 0;

/**
 * Setup function is called once at the start of the program.
 * It initializes the serial communication and sets the pin modes.
 */
void setup()
{
  Serial.begin(115200); // set the baud rate of the serial communication

  // set the motor pins as output
  for (int i = 0; i < 4; i++)
  {
    pinMode(Motors[i], OUTPUT);
  }

  // set the IR sensor pins as input
  for (int i = 0; i < 2; i++)
  {
    pinMode(IRSensors[i], INPUT);
  }
}

/**
 * Loop function is called repeatedly after the setup function.
 * It reads the values from the IR sensors, debounces them, and
 * controls the motors based on the debounced values.
 */
void loop()
{
  int leftIRValue = analogRead(IRSensors[0]);
  int rightIRValue = analogRead(IRSensors[1]);

  // Debounce IR sensor readings
  if (abs(leftIRValue - leftIRValuePrevious) > 50)
  {
    leftIRValuePrevious = leftIRValue;
  }
  if (abs(rightIRValue - rightIRValuePrevious) > 50)
  {
    rightIRValuePrevious = rightIRValue;
  }

  // Control the motors based on the debounced values
  if (leftIRValue == rightIRValue)
  {
    moveForward(); // move forward if the values are equal
  }
  else if (leftIRValue > rightIRValue)
  {
    turnLeft(); // turn left if the left value is greater than the right value
  }
  else if (leftIRValue < rightIRValue)
  {
    turnRight(); // turn right if the left value is less than the right value
  }

  delay(10); // wait for 10 milliseconds before taking the next reading
}

/**
 * Move the robot forward by setting the motor pins to the correct states.
 */
void moveForward()
{
  digitalWrite(Motors[0], HIGH);
  digitalWrite(Motors[1], LOW);
  digitalWrite(Motors[2], HIGH);
  digitalWrite(Motors[3], LOW);
}

/**
 * Turn the robot left by setting the motor pins to the correct states.
 */
void turnLeft()
{
  digitalWrite(Motors[0], LOW);
  digitalWrite(Motors[1], HIGH);
  digitalWrite(Motors[2], HIGH);
  digitalWrite(Motors[3], LOW);
}

/**
 * Turn the robot right by setting the motor pins to the correct states.
 */
void turnRight()
{
  digitalWrite(Motors[0], HIGH);
  digitalWrite(Motors[1], LOW);
  digitalWrite(Motors[2], LOW);
  digitalWrite(Motors[3], HIGH);
}

/**
 * Stop the motors by setting the motor pins to the correct states.
 */
void stopMotors()
{
  digitalWrite(Motors[0], LOW);
  digitalWrite(Motors[1], LOW);
  digitalWrite(Motors[2], LOW);
  digitalWrite(Motors[3], LOW);
}
