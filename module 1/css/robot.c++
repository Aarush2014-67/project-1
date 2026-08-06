#include <Servo.h>

// Motor Driver Pins (L298N)
#define ENA 5
#define IN1 6
#define IN2 7
#define ENB 10
#define IN3 8
#define IN4 9

// IR Line Sensors
#define LEFT_IR 2
#define RIGHT_IR 3

// Metal Sensor
#define METAL_SENSOR 4

// Servo
Servo sorter;
#define SERVO_PIN 11

void setup() {
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(METAL_SENSOR, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  sorter.attach(SERVO_PIN);
  sorter.write(90);   // Center position

  Serial.begin(9600);
}

void loop() {

  // Line Following
  int left = digitalRead(LEFT_IR);
  int right = digitalRead(RIGHT_IR);

  if(left == LOW && right == LOW) {
    forward();
  }
  else if(left == LOW && right == HIGH) {
    turnLeft();
  }
  else if(left == HIGH && right == LOW) {
    turnRight();
  }
  else {
    stopRobot();
  }

  // Waste Detection
  if(digitalRead(METAL_SENSOR) == HIGH) {
    stopRobot();
    delay(500);

    Serial.println("Non-Degradable Waste");

    sorter.write(150);    // Drop into non-degradable bin
    delay(1500);

    sorter.write(90);
    delay(500);
  }
  else {

    stopRobot();
    delay(500);

    Serial.println("Degradable Waste");

    sorter.write(30);     // Drop into degradable bin
    delay(1500);

    sorter.write(90);
    delay(500);
  }
}

// Motor Functions

void forward() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, 120);
  analogWrite(ENB, 180);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 120);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}