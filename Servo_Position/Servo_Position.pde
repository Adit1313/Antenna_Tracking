import processing.serial.*;
import java.awt.AWTException;
import java.awt.Robot;

Serial port;
int prevX, prevY;
Robot r;

boolean stop;

void setup() {
    size(720, 720);
    port = new Serial(this, Serial.list()[0], 9600);
    prevX = 0;
    prevY = 0;
    stop = false;
    try {
      r = new Robot();
    } catch(AWTException e) {
      println("Lol robot mar gaya");
    }
}

void draw() {
  if(!stop) {
    if (!(mouseX == prevX && mouseY == prevY)) {
      clear();
      background(255);
      line(mouseX, 0, mouseX, 720);
      line(0, mouseY, 720, mouseY);
      prevX = mouseX;
      prevY = mouseY;
    }
    port.write(mouseX + "\n");
    port.write(mouseY + "\n");
  }
}

void keyPressed() {
  if((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
    int keyIndex;
    if(key <= 'Z') {
      keyIndex = key-'A';
    } else {
      keyIndex = key-'a';
    }
    
    if (keyIndex == 15) {
      stop = !stop;
    }
    if (keyIndex == 17) {
      stop = true;
      port.write(360 + "\n");
      port.write(720 + "\n");
      r.mouseMove(686, 409);
      clear();
      background(255);
      line(360, 0, 360, 720);
      line(0, 360, 720, 360);
    }
  } 
}
