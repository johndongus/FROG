#include <TFT_eSPI.h>
#include "image_frames_anime_60.h" // Ensure this header contains frame data

#include "sensor.h"
#include "draw.h"

#define FRAME_DELAY 10
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
int currentFrame = 0;

PressureSensor pressureSensor(1);

void setup() {
    Serial.begin(115200);
    setupDisplay();
}

void loop() {
    float psi = pressureSensor.readValue();
    updateDisplay(psi, psi < 0, currentFrame);
    currentFrame = (currentFrame + 1) % FRAME_COUNT;
    delay(FRAME_DELAY);
}
