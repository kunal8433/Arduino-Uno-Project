#include <Servo.h>

Servo myservo;

#define trigPin 9
#define echoPin 8

#define MLa 4
#define MLb 5
#define MRa 6
#define MRb 7

long duration;
int distance;

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  return distance;
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

  myservo.attach(10);
  myservo.write(90);
}

void loop() {

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 15) {
    forward();
  }
  else {
    stopRobot();
    delay(200);

    backward();
    delay(400);

    stopRobot();
    delay(200);

    myservo.write(0);
    delay(500);

    myservo.write(180);
    delay(500);

    myservo.write(90);
    delay(300);

    left();
    delay(500);
  }
}