#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

class ntpHelper {
  private:
    int _requestInterval;
    long _gmtOffset;
    int _daylightOffset;
    const char* _ntpServer;
    time_t _lastNtpAccess;
    unsigned long _nextAccessMs;
    bool connect();

  public:
    ntpHelper(int requestInterval, const char* ntpServer, long gmtOffset, int daylightOffset);
    void Init();
    bool shouldSyncTime();
    void getNtpTime(struct tm * info);
};