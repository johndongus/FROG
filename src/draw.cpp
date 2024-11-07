#include "draw.h"
#include "image_frames_anime_60.h"
extern TFT_eSPI tft;
extern TFT_eSprite sprite;

void setupDisplay() {
    tft.begin();
    tft.setRotation(1);
    tft.setSwapBytes(false);
    tft.invertDisplay(true);
    tft.fillScreen(TFT_BLACK);
}

void renderGIFFrame(int frameIndex) {
    const uint16_t* frameData = nullptr;
    switch (frameIndex) {
        case 0: frameData = frame_0; break;
        case 1: frameData = frame_1; break;
        // Add cases for all frames
    }
    for (int y = 0; y < 70; y++) {
        for (int x = 0; x < 70; x++) {
            sprite.drawPixel(x + 125, y + 80, frameData[y * 70 + x]);
        }
    }
}

void updateDisplay(float psi, bool isVacuum, int frameIndex) {
    sprite.createSprite(320, 170);
    sprite.fillSprite(TFT_BLACK);
    sprite.drawRect(1, 0, sprite.width() - 1, sprite.height() - 1, TFT_WHITE);

    renderGIFFrame(frameIndex);
    uint16_t textColor = (psi <= 4) ? TFT_WHITE : (psi <= 8) ? sprite.color565(0, 255, 0) : TFT_RED;

    sprite.setTextColor(textColor, TFT_BLACK);
    sprite.setCursor(60, 130);
    sprite.print(isVacuum ? psi * 2.036 : psi);
    sprite.pushSprite(0, 0);
    sprite.deleteSprite();
}
