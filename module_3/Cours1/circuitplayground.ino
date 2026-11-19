#include <Adafruit_CircuitPlayground.h>

const float SHAKE_THRESHOLD = 20.0;
const unsigned long SHAKE_COOLDOWN = 500;
const int PIXELS = 10;

const uint32_t PALETTE[] = {0xc9422c, 0xb27728, 0x397b68, 0x60599b};
const int PALETTE_SIZE = sizeof(PALETTE) / sizeof(PALETTE[0]);

bool lastBtn1 = false;
bool lastBtn2 = false;
unsigned long lastShakeTime = 0;

String incoming;
long score = 0;
bool celebrating = false;
unsigned long celebrationStart = 0;
int lastFrame = -1;

void showScore(int lit) {
  CircuitPlayground.strip.clear();
  for (int pixel = 0; pixel < lit; pixel++) {
    CircuitPlayground.strip.setPixelColor(pixel, PALETTE[0]);
  }
  CircuitPlayground.strip.show();
}

void setScore(long newScore) {
  if (newScore < 0 || newScore == score) return;
  score = newScore;

  if (score == 0) celebrating = false;
  if (score > 0 && score % PIXELS == 0) {
    showScore(PIXELS);
    celebrating = true;
    celebrationStart = millis();
    lastFrame = -1;
  } else if (!celebrating) {
    showScore(score % PIXELS);
  }
}

void readScore() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      if (incoming.startsWith("score:")) {
        setScore(incoming.substring(6).toInt());
      }
      incoming = "";
    } else if (incoming.length() < 24) {
      incoming += c;
    }
  }
}

void animateRing() {
  if (!celebrating) return;
  unsigned long elapsed = millis() - celebrationStart;

  if (elapsed < 150) return;
  if (elapsed >= 1350) {
    celebrating = false;
    showScore(score % PIXELS);
    return;
  }

  int frame = (elapsed - 150) / 80;
  if (frame == lastFrame) return;
  lastFrame = frame;

  for (int pixel = 0; pixel < PIXELS; pixel++) {
    int position = (pixel + frame) % PIXELS;
    int colorIndex = position * PALETTE_SIZE / PIXELS;
    CircuitPlayground.strip.setPixelColor(pixel, PALETTE[colorIndex]);
  }
  CircuitPlayground.strip.show();
}

void setup() {
  Serial.begin(115200);
  CircuitPlayground.begin();
  showScore(0);
}

void loop() {
  bool btn1 = CircuitPlayground.leftButton();
  if (btn1 && !lastBtn1) Serial.println("btn1");
  lastBtn1 = btn1;

  bool btn2 = CircuitPlayground.rightButton();
  if (btn2 && !lastBtn2) Serial.println("btn2");
  lastBtn2 = btn2;

  float x = CircuitPlayground.motionX();
  float y = CircuitPlayground.motionY();
  float z = CircuitPlayground.motionZ();
  float totalAccel = sqrt(x * x + y * y + z * z);

  if (totalAccel > SHAKE_THRESHOLD && millis() - lastShakeTime > SHAKE_COOLDOWN) {
    Serial.println("shake");
    lastShakeTime = millis();
  }

  readScore();
  animateRing();
  delay(20);
}
