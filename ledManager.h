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
    uint32_t _tickIntervalMs = 1000U;
    hw_timer_t *_ticker = NULL;
  public:
    /// @brief Creates a new instance of an led manager
    /// @param tickIntervalMs The frequency that the rules will be evaluated 
    /// @param defaultFrequency the default PWM frequency
    /// @param defaultResolution the default PWM resolution
    ledManager(uint32_t tickIntervalMs = 1000U, uint32_t defaultFrequency = 5000U, uint8_t defaultResolution = 8);

    /// @brief Indicates the duration between rule checks
    /// @param tickIntervalMs interval in ms
    void setRuleCheckInterval(u_int32_t tickIntervalMs);

    /// @brief Starts the led manager
    void start();

    /// @brief Add a single led
    /// @param ledPin led pin
    /// @return true on success
    bool addSimple(int ledPin);

    /// @brief Add a single led, overriding the default frequency and resolution
    /// @param ledPin led pin
    /// @param frequency the PWM frequency
    /// @param resolution the PWM resolution
    /// @return 
    bool addSimple(int ledPin, uint32_t frequency, uint8_t resolution);

    /// @brief Add a three channel RGB led
    /// @param redPin red channel pin
    /// @param greenPin green channel pin
    /// @param bluePin blue channel pin
    /// @param targetColour the desired RGB colour at full brightness
    /// @return 
    bool addRgb(int redPin, int greenPin, int bluePin, rgb targetColour = {255,255,255});
    
    /// @brief Add a three channel RGB led, overriding the default frequency and resolution
    /// @param redPin red channel pin
    /// @param greenPin green channel pin
    /// @param bluePin blue channel pin
    /// @param frequency the PWM frequency
    /// @param resolution the PWM resolution
    /// @param targetColour the desired RGB colour at full brightness
    /// @return 
    bool addRgb(int redPin, int greenPin, int bluePin, uint32_t frequency, uint8_t resolution, rgb targetColour = {255,255,255});
};