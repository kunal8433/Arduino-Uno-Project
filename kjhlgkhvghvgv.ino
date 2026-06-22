#include <Servo.h>

Servo myservo;

// Ultrasonic pins (MATCH your wiring)
#define trigPin 8
#define echoPin 9

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

  // timeout added (VERY IMPORTANT for stability)
  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return 999; // no reading = no obstacle

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

void right() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
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

  // FILTER noise (important)
  if (distance > 0 && distance < 15) {
    stopRobot();
    delay(200);

    backward();
    delay(300);

    stopRobot();
    delay(200);

    myservo.write(0);
    delay(400);

    int leftDist = getDistance();

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

    delay(500);
  }
  else {
    forward();
  }
}
