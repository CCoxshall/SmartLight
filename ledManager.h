#pragma once

#include <Arduino.h>
#include <vector>
#include "ledController.h"
#include "rgb.h"

class ledManager {
  private:
    std::vector<ledController*> Controllers = {};
    uint8_t _nextPwmChannel = 0;
    uint32_t _defaultFrequency = 5000U;
    uint8_t _defaultResolution = 8;
    uint8_t _tickIntervalMs = 1000U;
    hw_timer_t *_ticker = NULL;
  public:
    /// @brief Creates a new instance of an led manager
    /// @param defaultFrequency 
    /// @param defaultResolution 
    ledManager(uint32_t tickIntervalMs = 1000U, uint32_t defaultFrequency = 5000U, uint8_t defaultResolution = 8);
    void start();
    bool addSimple(int ledPin);
    bool addSimple(int ledPin, uint32_t frequency, uint8_t resolution);
    bool addRgb(int redPin, int greenPin, int bluePin, rgb colour = {255,255,255});
    bool addRgb(int redPin, int greenPin, int bluePin, uint32_t frequency, uint8_t resolution, rgb colour = {255,255,255});
};