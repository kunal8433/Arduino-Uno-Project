
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LEFT_FWD   17
#define LEFT_REV   18
#define RIGHT_FWD  15
#define RIGHT_REV  16

BLECharacteristic *pCharacteristic;
String rxValue = "";

void stopCar() {
  digitalWrite(LEFT_FWD, LOW);
  digitalWrite(LEFT_REV, LOW);
  digitalWrite(RIGHT_FWD, LOW);
  digitalWrite(RIGHT_REV, LOW);
}

void forward() {
  digitalWrite(LEFT_FWD, HIGH);
  digitalWrite(LEFT_REV, LOW);
  digitalWrite(RIGHT_FWD, HIGH);
  digitalWrite(RIGHT_REV, LOW);
}

void backward() {
  digitalWrite(LEFT_FWD, LOW);
  digitalWrite(LEFT_REV, HIGH);
  digitalWrite(RIGHT_FWD, LOW);
  digitalWrite(RIGHT_REV, HIGH);
}

void left() {
  digitalWrite(LEFT_FWD, LOW);
  digitalWrite(LEFT_REV, LOW);
  digitalWrite(RIGHT_FWD, HIGH);
  digitalWrite(RIGHT_REV, LOW);
}

void right() {
  digitalWrite(LEFT_FWD, HIGH);
  digitalWrite(LEFT_REV, LOW);
  digitalWrite(RIGHT_FWD, LOW);
  digitalWrite(RIGHT_REV, LOW);
}

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();

    if (value == "F") forward();
    if (value == "B") backward();
    if (value == "L") left();
    if (value == "R") right();
    if (value == "S") stopCar();
  }
};

void setup() {
  Serial.begin(115200);

  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_REV, OUTPUT);

  stopCar();

  BLEDevice::init("My_RC_Car");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService =
  pServer->createService("12345678-1234-1234-1234-123456789abc");

  pCharacteristic = pService->createCharacteristic(
                      "abcd1234-ab12-cd34-ef56-1234567890ab",
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE Ready");
}

void loop() {}