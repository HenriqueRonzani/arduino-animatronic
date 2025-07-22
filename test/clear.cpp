#include <Servo.h>

Servo servo9;

void setup() {
  servo9.attach(9);
  servo9.write(100);
}

void loop() {
}
