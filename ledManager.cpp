#include "ledManager.h"
#include "rgb.h"
#include "rgbController.h"

void IRAM_ATTR timerCallback()
{
  Serial.printf("Tick at %d", millis());
  Serial.println();
}

ledManager::ledManager(uint32_t tickIntervalMs, uint32_t frequency, uint8_t resolution)
{
  _defaultFrequency = frequency;
  _defaultResolution = resolution;
  _tickIntervalMs = tickIntervalMs;
}

void ledManager::setRuleCheckInterval(u_int32_t tickIntervalMs)
{
  _tickIntervalMs = tickIntervalMs;
  if(_ticker != NULL && timerStarted(_ticker)){
    timerStop(_ticker);
    timerAlarmDisable(_ticker);
    timerDetachInterrupt(_ticker);
    timerAttachInterrupt(_ticker, &timerCallback, true);
    timerAlarmWrite(_ticker, _tickIntervalMs * 1000, true);
    timerAlarmEnable(_ticker);
    timerStart(_ticker);
  }
}

void ledManager::start()
{
  Serial.printf("Clock speed: %dmHz", APB_CLK_FREQ / 1000000);
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

  // TODO - implement lol
  return true;
}

bool ledManager::addRgb(int redPin, int greenPin, int bluePin, rgb targetColour) 
{
  return addRgb(redPin, greenPin, bluePin, _defaultFrequency, _defaultResolution, targetColour);
}

bool ledManager::addRgb(int redPin, int greenPin, int bluePin, uint32_t frequency, uint8_t resolution, rgb targetColour)
{
  if(_nextPwmChannel + 3 > 15) {
    Serial.printf("Unable to add the RGB at pins %n, %n & %n. Maximum number of PWM channels exceeded (15)", redPin, greenPin, bluePin);
    Serial.println();
    return false;
  }

  rgbController controller = {targetColour.Red, targetColour.Green, targetColour.Blue};
  if (controller.Init(redPin, greenPin, bluePin, _nextPwmChannel++, _nextPwmChannel++, _nextPwmChannel++))
  {
      Serial.println("Adding RGB controller to collection");
      Controllers.push_back(&controller);
      return true;
  }
  return false;
}