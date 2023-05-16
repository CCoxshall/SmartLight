#pragma once

#include <Arduino.h>
#include "rgb.h"
#include "ledController.h"

class rgbController : public ledController {
  private:
    int _channel_Red;
    int _channel_Green;
    int _channel_Blue;

    int _maxRed;
    int _maxGreen;
    int _maxBlue;

    bool _enabled;

  public:
    rgbController(unsigned char maxRed, unsigned char maxGreen, unsigned char maxBlue);
    bool Init(int redPin, int greenPin, int bluePin, uint8_t redChannel, uint8_t greenChannel, uint8_t blueChannel, uint32_t frequency = 5000, uint8_t resolution = 8);
    void setBrightness(unsigned char level);
    void setColour(unsigned char r, unsigned char g, unsigned char b);
    rgb getColour();
};