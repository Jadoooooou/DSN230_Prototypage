#include <Adafruit_CircuitPlayground.h>

int path[] = {7, 8, 9, 0, 1, 2}; // tableau des points de la "balle"
int pos = 2; // index actuel dans path[]
int dir = 1; // direction (+/-)

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(path[pos], 255, 255, 255);
  delay(800);

  // une fois au bout, appuyer sur le bon bouton
  if (path[pos] == 7) { 
    if (!waitForButton(false, 800)) {
      gameOver();
      return;
    }
  } else if (path[pos] == 2) { 
    if (!waitForButton(true, 800)) {
      gameOver();
      return;
    }
  }

  // change la direction aux bouts
  pos += dir;
  if (pos == 0 || pos == 5) dir = -dir;
}

// Vérifie le bon bouton pendant "windowMs" millisecondes
bool waitForButton(bool needLeft, int windowMs) {
  unsigned long start = millis();
  while (millis() - start < windowMs) {
    if (needLeft && CircuitPlayground.leftButton()) return true;
    if (!needLeft && CircuitPlayground.rightButton()) return true;
  }
  return false;
}

// animation de Game Over
void gameOver() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  }
  CircuitPlayground.strip.show();
  // music "wawawawaa"
  //CircuitPlayground.playTone(330, 200);
  //delay(50);
  //CircuitPlayground.playTone(294, 200);
  //delay(50);
  //CircuitPlayground.playTone(262, 200);
  //delay(50);
  //CircuitPlayground.playTone(247, 500);
  delay(2000);
  pos = 2; 
  dir = 1;
}


