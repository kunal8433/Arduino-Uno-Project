#include <Servo.h>

Servo myservo;

#define trigPin 9
#define echoPin 8

#define MLa 4
#define MLb 5
#define MRa 6
#define MRb 7

long duration, distance;

long getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  return distance;
}

void forward()
{
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);

  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
}

void stopRobot()
{
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);

  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
}

void backward()
{
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);

  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
}

void leftTurn()
{
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);

  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
}

void rightTurn()
{
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);

  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
}

void setup()
{
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);

  myservo.attach(10);
  myservo.write(90);

  delay(1000);
}

void loop()
{
  myservo.write(90);
  delay(300);

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 20 || distance == 0)
  {
    forward();
  }
  else
  {
    stopRobot();
    delay(300);

    backward();
    delay(400);
    stopRobot();

    // Left check
    myservo.write(0);
    delay(500);
    long leftDist = getDistance();

    // Right check
    myservo.write(180);
    delay(500);
    long rightDist = getDistance();

    // Center servo
    myservo.write(90);
    delay(300);

    if (leftDist > rightDist)
    {
      leftTurn();
      delay(600);
    }
    else
    {
      rightTurn();
      delay(600);
    }

    stopRobot();
  }
}
