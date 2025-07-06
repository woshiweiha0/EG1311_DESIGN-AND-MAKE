/*
  // EG1311 B13 Group 4
  // AY24/25 Sem 2, 14 April 2025
  // This file contains the source code that was deployed in Final
  Prototype and Final Prototype Lite, capable of commanding a robot
  to move forward, stop when a wall is detected, launch a ping-pong
  ball via a catapult, before reversing indefinitely.
*/  

#include <Servo.h>

Servo servo;
int TRIG_PIN = 13;
int ECHO_PIN = 12;
int SERVO_PIN = 11;
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
float SPEED_OF_SOUND = 0.0345;
int catapult_launched = 0; // Initialise catapult launched to be false
int counter = 0;

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN); // Not <500 or >2500
  servo.write(0);
  catapult_launched = 0;
  Serial.begin(9600); // Comment out for actual run
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms = microsecs*SPEED_OF_SOUND/2;
  Serial.println(cms); // Comment out for actual run

  digitalWrite(MOTOR_PIN1, LOW); // All motors to go forward
  digitalWrite(MOTOR_PIN2, HIGH);

  // This counter is deployed to eliminate phantom detections
  counter = 0; // Reset counter to 0 every loop
  if (cms < 18) { // Count to 3 when wall detected
    while (cms < 18 && counter <= 3)
    counter += 1;
  } // Exit loop when counter equal to 3

  if (counter >= 3) {
    digitalWrite(MOTOR_PIN1, LOW); // Stop all motor
    digitalWrite(MOTOR_PIN2, LOW);
    delay(1500);
    servo.write(70); // Launch catapult
    catapult_launched = 1;
    delay(1500);

    // Robot will reverse indefinitely once the while-loop is entered
    while (catapult_launched == 1) { // Catapult launched set to true
      digitalWrite(MOTOR_PIN1, HIGH); // Motors draws reverse current
      digitalWrite(MOTOR_PIN2, LOW);
    }
  } 
  delay(10);
}


