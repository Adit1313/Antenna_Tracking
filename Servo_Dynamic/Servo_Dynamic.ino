#include <Servo.h>

Servo bottom, top;

int posX, posY;
char input;

void setup() {
  bottom.attach(9);
  top.attach(10);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    posX = 0;
    posY = 0;
    while(1) {
      input = Serial.read();
      if (input == '\n') break;
      if (input == -1) continue;
      posX *= 10;
      posX = ((input - 48) + posX);
    }
    while(1) {
      input = Serial.read();
      if (input == '\n') break;
      if (input == -1) continue;
      posY *= 10;
      posY = ((input - 48) + posY);
    }
    posX = map(posX, 0, 720, 180, 0);
    posY = map(posY, 0, 720, 180, 90);
    bottom.write(posX);
   
    top.write(posY);
  }
}
