#include "esp32-hal.h"
#include <WiFi.h>
#include "time.h"
#include "ntpHelper.h"

ntpHelper::ntpHelper(int requestInterval, const char* ntpServer, long gmtOffset, int daylightOffset) {
  _lastNtpAccess = time(NULL);
  _requestInterval = requestInterval;
  _ntpServer = ntpServer;
  _gmtOffset = gmtOffset;
  _daylightOffset = daylightOffset;
};

void ntpHelper::Init() {

}

void ntpHelper::getNtpTime(struct tm * info) {

  if(!shouldSyncTime() && getLocalTime(info)) {
    return;
  }

  Serial.println("Attempting to get time from ntp server...");

  if(!connect()) {
    getLocalTime(info);
    return;
  }
  
  // Init and get the time
  configTime(_gmtOffset, _daylightOffset, _ntpServer);

  if(getLocalTime(info)) {
    Serial.print("Retrieved the time at ");
    Serial.println(info, "%A, %B %d %Y %H:%M:%S");
    _lastNtpAccess = mktime(info);
    _nextAccessMs = millis() + (_requestInterval * 1000);
  }

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  return;
};

bool ntpHelper::shouldSyncTime() {
  return millis() > _nextAccessMs;
};

bool ntpHelper::connect() {
    if(WiFi.getMode() == WIFI_OFF) {
    WiFi.mode(WIFI_STA);
    WiFi.reconnect();
  }

  long ms = millis();
  while (WiFi.status() != WL_CONNECTED) {

    if(millis() - ms > 10000) {
      Serial.println("Failed to connect to WiFi.");
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      return false;
    }

    delay(500);
  };
  return true;
}