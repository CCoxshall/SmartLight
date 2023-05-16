#include "HardwareSerial.h"
#include "esp32-hal-ledc.h"
#include "rgbController.h"

rgbController::rgbController(unsigned char maxRed, unsigned char maxGreen, unsigned char maxBlue) {
  _maxRed = maxRed;
  _maxGreen = maxGreen;
  _maxBlue = maxBlue;
  _enabled = false;
}

bool rgbController::Init(int redPin, int greenPin, int bluePin, uint8_t redChannel, uint8_t greenChannel, uint8_t blueChannel, uint32_t frequency, uint8_t resolution) {

  _channel_Red = redChannel;
  _channel_Green = greenChannel;
  _channel_Blue = blueChannel;

  _enabled = true;

  if(ledcSetup(_channel_Red, frequency, resolution) == 0) {
    Serial.println("Failed to set up the Red PWM channel.");
    _enabled = false;
  }

  if(ledcSetup(_channel_Green, frequency, resolution) == 0) {
    Serial.println("Failed to set up the Green PWM channel.");
    _enabled = false;
  }
  
  if(ledcSetup(_channel_Blue, frequency, resolution) == 0) {
    Serial.println("Failed to set up the Blue PWM channel.");
    _enabled = false;
  }  

  if(_enabled) {
    ledcAttachPin(redPin, redChannel);
    ledcAttachPin(greenPin, greenChannel);
    ledcAttachPin(bluePin, blueChannel);
  }

  return _enabled;
}

void rgbController::setBrightness(unsigned char level) {

  if(!_enabled) {
    return;
  }

  if(level > 255) {
    level = 255;
  }

  long calcR = map(level, 0, 255, 0, _maxRed);
  long calcG = map(level, 0, 255, 0, _maxGreen);
  long calcB = map(level, 0, 255, 0, _maxBlue);

  Serial.print("Setting strip to ");
  Serial.print(calcR);
  Serial.print(", ");
  Serial.print(calcG);
  Serial.print(", ");
  Serial.print(calcB);
  Serial.println();

  ledcWrite(_channel_Red, calcR);
  ledcWrite(_channel_Green, calcG);
  ledcWrite(_channel_Blue, calcB);
}

void rgbController::setColour(unsigned char r, unsigned char g, unsigned char b) {
  _maxRed = r;
  _maxGreen = g;
  _maxBlue = b;
}

rgb rgbController::getColour() {

  rgb Rgb;

  Rgb.Red = ledcRead(_channel_Red);
  Rgb.Green = ledcRead(_channel_Green);
  Rgb.Blue = ledcRead(_channel_Blue);

  return Rgb;
}
