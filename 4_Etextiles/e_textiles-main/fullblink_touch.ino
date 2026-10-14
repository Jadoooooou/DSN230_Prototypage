#include <Adafruit_CircuitPlayground.h>

// Baseline capacitive values captured at boot
int baseA1 = 0;
int baseA3 = 0;
int baseA4 = 0;
int baseA7 = 0;

// Increase over baseline required to register a touch.
// Raise this number (e.g. 500) if it triggers too easily, 
// or lower it (e.g. 150) if it doesn't detect soft touches.
const int TOUCH_OFFSET = 250;

void setup() {
  CircuitPlayground.begin();
  delay(1000); // Give touch sensing time to settle

  // Calibrate baseline values (do NOT touch pads when powering on)
  baseA1 = CircuitPlayground.readCap(A1);
  baseA3 = CircuitPlayground.readCap(A3);
  baseA4 = CircuitPlayground.readCap(A4);
  baseA7 = CircuitPlayground.readCap(A7);
}

void loop() {
  // Read current touch readings
  int touchA1 = CircuitPlayground.readCap(A1);
  int touchA3 = CircuitPlayground.readCap(A3);
  int touchA4 = CircuitPlayground.readCap(A4);
  int touchA7 = CircuitPlayground.readCap(A7);

  // Check which pads are currently touched
  bool pressedA1 = touchA1 > (baseA1 + TOUCH_OFFSET);
  bool pressedA3 = touchA3 > (baseA3 + TOUCH_OFFSET);
  bool pressedA4 = touchA4 > (baseA4 + TOUCH_OFFSET);
  bool pressedA7 = touchA7 > (baseA7 + TOUCH_OFFSET);

  if (pressedA1) {
    // Pad A1: Red ring
    setAllPixels(255, 0, 0);
  } 
  else if (pressedA3) {
    // Pad A3: Green ring
    setAllPixels(0, 255, 0);
  } 
  else if (pressedA4) {
    // Pad A4: Blue ring
    setAllPixels(0, 0, 255);
  } 
  else if (pressedA7) {
    // Pad A7: Yellow ring
    setAllPixels(255, 255, 0);
  } 
  else {
    // No pad touched: Turn off ring
    CircuitPlayground.clearPixels();
  }

  delay(20); // Small stability delay
}

// Helper function to set all 10 NeoPixels to one color
void setAllPixels(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, r, g, b);
  }
}