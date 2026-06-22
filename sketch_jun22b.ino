#include <Servo.h>

Servo myservo;

// Ultrasonic pins
#define trigPin 8
#define echoPin 9

// Motor pins
#define MLa 4
#define MLb 5
#define MRa 6
#define MRb 7

// Motor speed pins (IMPORTANT for speed control)
#define ENA 3
#define ENB 11

long duration;
int distance;

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return 999;

  int dist = duration * 0.034 / 2;
  return dist;
}

void forward() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
}

void backward() {
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
}

void left() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
}

void right() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
}

void stopRobot() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // 🔥 HALF SPEED (adjust here)
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);

  myservo.attach(10);
  myservo.write(90);
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 15) {

    stopRobot();
    delay(200);

    backward();
    delay(200);

    stopRobot();
    delay(200);

    // look left
    myservo.write(0);
    delay(400);
    int leftDist = getDistance();

    // look right
    myservo.write(180);
    delay(400);
    int rightDist = getDistance();

    myservo.write(90);
    delay(300);

    if (leftDist > rightDist) {
      left();
    } else {
      right();
    }

    delay(400);
  }
  else {
    forward();
  }
}