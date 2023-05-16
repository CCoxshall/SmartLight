#include <WiFi.h>
#include "time.h"
#include "ntpHelper.h"
#include "ledManager.h"
#include "rgbController.h"

//const char* ssid     = "VM946496-2G";
//const char* password = "technics1200";

const char* ssid     = "Get Off My LAN";
const char* password = "SitOnMyFace?";

ntpHelper _ntpHelper = {86400, "0.pool.ntp.org", 0, 0};
rgbController _strip1     = {255, 255, 255}; // final R G B 
ledManager _ledManager;

int daytimeStart = 8;
int nightStart = 20;
int transitionTimeInSeconds = 60;

enum LightCycle {
  On,
  Off,
  Increasing,
  Decreasing
};

LightCycle currentStatus = Off;




void setup(){
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // get the time from the ntp server
  _ntpHelper.Init();

  _ledManager.addRgb(27, 26, 25, {255,128,64});
  _ledManager.start();
}

void loop(){
  struct tm now;
  _ntpHelper.getNtpTime(&now);
  
  UpdateRgb();

  // if(currentStatus == Increasing || currentStatus == Decreasing) {
  //   UpdateRgb();
  // }
  // else if(now.tm_hour > nightStart && currentStatus == On) {
  //   Serial.println("Turning the light off.");
  //   currentStatus = Decreasing;
  //   UpdateRgb();
  // }
  // else if(now.tm_hour > daytimeStart && currentStatus == Off) {
  //   Serial.println("Turning the light on.");
  //   currentStatus = Increasing;
  //   UpdateRgb();
  // }

  delay(100);
}

bool up = true;
unsigned char currentBrightness = 0;
void UpdateRgb() {
  if(currentBrightness <= 1 && !up){
    currentBrightness = 0;
    up = !up;
  }
  else if(currentBrightness >= 254 && up){
    currentBrightness = 255;
    up = !up;
  }
  else {
    currentBrightness += up ? 1 : -1;
  }
  _strip1.setBrightness(currentBrightness);
}