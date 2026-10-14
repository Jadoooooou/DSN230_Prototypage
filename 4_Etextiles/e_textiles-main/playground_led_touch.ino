#include <Adafruit_CircuitPlayground.h>

// Baseline capacitive values captured at boot
int baseA1 = 0;
int baseA3 = 0;
int baseA4 = 0;
int baseA7 = 0;

// Increase over baseline required to register a touch.
// Raise number (e.g. 500) if too sensitive, or lower it if it doesn't detect soft touches.

const int TOUCH_OFFSET = 250;

void setup() {
  CircuitPlayground.begin();
  delay(1000); // Give touch sensing time to settle

  // Calibrate baseline values (ensure you are NOT touching the pads when powering on)
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

  // --- Pad A1 (Pixel 6 - Red) ---
  if (touchA1 > (baseA1 + TOUCH_OFFSET)) {
    CircuitPlayground.setPixelColor(6, 255, 0, 0);   // Red when touched
  } else {
    CircuitPlayground.setPixelColor(6, 0, 0, 0);     // Off
  }

  // --- Pad A3 (Pixel 9 - Green) ---
  if (touchA3 > (baseA3 + TOUCH_OFFSET)) {
    CircuitPlayground.setPixelColor(9, 0, 255, 0);   // Green when touched
  } else {
    CircuitPlayground.setPixelColor(9, 0, 0, 0);     // Off
  }

  // --- Pad A4 (Pixel 0 - Blue) ---
  if (touchA4 > (baseA4 + TOUCH_OFFSET)) {
    CircuitPlayground.setPixelColor(0, 0, 0, 255);   // Blue when touched
  } else {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);     // Off
  }

  // --- Pad A7 (Pixel 3 - Yellow) ---
  if (touchA7 > (baseA7 + TOUCH_OFFSET)) {
    CircuitPlayground.setPixelColor(3, 255, 255, 0); // Yellow when touched
  } else {
    CircuitPlayground.setPixelColor(3, 0, 0, 0);     // Off
  }

  delay(20); // Small stability delay
}