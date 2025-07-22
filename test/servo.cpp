#include <Servo.h>

const Servo servo9;
const int buzzerPin = 10;

void setup() {
  servo9.attach(9);
  moveServo(0, servo9);
  delay(10000);
}

void loop() {
  servo.write(90);
  delay(10000);
  tone(buzzerPin, 1000, 1000);
  tone(buzzerPin, 1000, 1000);
  delay(5000);
  servo.write(180);
  delay(10000);
  tone(buzzerPin, 1000, 1000);
  tone(buzzerPin, 1000, 1000);
  delay(5000);
  servo.write(90);
  delay(10000);
  tone(buzzerPin, 1000, 1000);
  tone(buzzerPin, 1000, 1000);
  delay(5000);
  servo.write(0);
  delay(10000);
  tone(buzzerPin, 1000, 1000);
  tone(buzzerPin, 1000, 1000);
  delay(5000);
}
