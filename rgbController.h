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
    /// @brief Creates a new rgbController instance
    /// @param maxRed target red channel intensity (0-255)
    /// @param maxGreen target green channel intensity (0-255)
    /// @param maxBlue target blue channel intensity (0-255)
    rgbController(unsigned char maxRed, unsigned char maxGreen, unsigned char maxBlue);
    
    /// @brief Initialises the rgb controller
    /// @param redPin Output pin for the red channel
    /// @param greenPin Output pin for the green channel
    /// @param bluePin Output pin for the blue channel
    /// @param redChannel PWM channel for the red led
    /// @param greenChannel PWM channel for the green led
    /// @param blueChannel PWM channel for the blue led
    /// @param frequency PWM frequency
    /// @param resolution PWM resolution
    /// @return 
    bool Init(int redPin, int greenPin, int bluePin, uint8_t redChannel, uint8_t greenChannel, uint8_t blueChannel, uint32_t frequency = 5000, uint8_t resolution = 8);

    /// @brief Sets the brightness levels of all leds
    /// @param level the desired level (0-255)
    void setBrightness(unsigned char level);

    /// @brief Sets the desired RGB when at full intensity
    /// @param r Red channel (0-255)
    /// @param g Green channel (0-255)
    /// @param b Blue channel (0-255)
    void setTargetRGB(unsigned char r, unsigned char g, unsigned char b);

    /// @brief Gets the current RGB values
    /// @return Current RGB values
    rgb getCurrentRGB();
};