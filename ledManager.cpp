#include "esp_clk.h"
#include "ledManager.h"
#include "rgb.h"
#include "rgbController.h"

void IRAM_ATTR timerCallback()
{
  Serial.printf("Tick at %n", millis());
  Serial.println();
}

ledManager::ledManager(uint32_t tickIntervalMs, uint32_t frequency, uint8_t resolution)
{
  _defaultFrequency = frequency;
  _defaultResolution = resolution;
  _tickIntervalMs = tickIntervalMs;
}

void ledManager::start() 
{
  // interval = ticks * (clock speed / prescaler)
  uint32_t clockSpeed = 80000000U;
  uint32_t prescaler = 80U;

  Serial.printf("Clock speed: %n", clockSpeed);
  Serial.println();

  _ticker = timerBegin(0, 80, true);
  timerAttachInterrupt(_ticker, &timerCallback, true);
  timerAlarmWrite(_ticker, _tickIntervalMs * 1000, true);
  timerAlarmEnable(_ticker);
}

bool ledManager::addSimple(int ledPin)
{
  return addSimple(ledPin, _defaultFrequency, _defaultResolution);
}

bool ledManager::addSimple(int ledPin, uint32_t frequency, uint8_t resolution)
{
  if(_nextPwmChannel == 15) {
    Serial.printf("Unable to add the LED at pin %n. Maximum number of PWM channels exceeded (15)", ledPin);
    Serial.println();
    return false;
  }
}

bool ledManager::addRgb(int redPin, int greenPin, int bluePin, rgb colour) 
{
  return addRgb(redPin, greenPin, bluePin, _defaultFrequency, _defaultResolution, colour);
}

bool ledManager::addRgb(int redPin, int greenPin, int bluePin, uint32_t frequency, uint8_t resolution, rgb colour)
{
  if(_nextPwmChannel + 3 > 15) {
    Serial.printf("Unable to add the RGB at pins %n, %n & %n. Maximum number of PWM channels exceeded (15)", redPin, greenPin, bluePin);
    Serial.println();
    return false;
  }

  rgbController controller = {colour.Red, colour.Green, colour.Blue};
  if (controller.Init(redPin, greenPin, bluePin, _nextPwmChannel++, _nextPwmChannel++, _nextPwmChannel++))
  {
      Controllers.push_back(&controller);
      return true;
  }
  return false;
}