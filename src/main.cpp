#include <Arduino.h>

const int sensorPins[] = {2, 3}; // Left and Right IR sensor pins
const int motorPins[] = {4, 6};   // Motor A and Motor B (forward)

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < 2; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW); // Initially stop both motors
  }
  
  for (int i = 0; i < 2; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {
  int sensorValues[2];
  for (int i = 0; i < 2; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
  }
  
  Serial.print("Left Sensor: ");
  Serial.print(sensorValues[0]);
  Serial.print(" | Right Sensor: ");
  Serial.println(sensorValues[1]);
  
  if (sensorValues[0] == LOW && sensorValues[1] == LOW) {
    moveForward();
  } 
  else if (sensorValues[0] == HIGH && sensorValues[1] == LOW) {
    turnRight();
  } 
  else if (sensorValues[0] == LOW && sensorValues[1] == HIGH) {
    turnLeft();
  } 
  else {
    stopMotors();
  }
}

void moveForward() {
  digitalWrite(motorPins[0], HIGH);  // Move left motor forward
  digitalWrite(motorPins[1], HIGH); // Move right motor forward
}

void turnLeft() {
  digitalWrite(motorPins[0], LOW);   // Stop left motor
  digitalWrite(motorPins[1], HIGH); // Move right motor forward
}

void turnRight() {
  digitalWrite(motorPins[0], HIGH);  // Move left motor forward
  digitalWrite(motorPins[1], LOW);  // Stop right motor
}

void stopMotors() {
  digitalWrite(motorPins[0], LOW);   // Stop left motor
  digitalWrite(motorPins[1], LOW);  // Stop right motor
}