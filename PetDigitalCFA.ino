#include "petDigitalServer.h"
#include "petDigitalMotionTracker.h"

// apenas para DOIT ESP32 DEVKIT V1
static const uint8_t LED_BUILTIN = 2;
#define BUILTIN_LED LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN

unsigned long start;

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(5000);
  Serial.print("\n");
  initFileSystem();
  initWiFi();
  initTime();
  initWebServer();
  initMPU9250();
  start = millis();
}

long int i = 0;

void loop()
{
  server.handleClient();
  delay(2); // allow the cpu to switch to other tasks
  if (millis() - start > 1000)
  {
    start = millis();
    printLocalTime();
    statusMPU9250();
  }
  
}