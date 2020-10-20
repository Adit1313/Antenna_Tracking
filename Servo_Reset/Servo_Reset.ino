#include <Servo.h>

Servo bottom, top;
int pos = 90;

void setup() {
  bottom.attach(9);
  top.attach(10);
}

void loop() {
  bottom.write(pos - 10);
  top.write(pos - 10);
}
