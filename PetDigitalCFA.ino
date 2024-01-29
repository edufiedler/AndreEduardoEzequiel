#include "petDigitalServer.h"
#include "petDigitalMotionTracker.h"
#include "petDigitalTempSensors.h"
#include "petDigitalPulseSensor.h"

// apenas para DOIT ESP32 DEVKIT V1
static const uint8_t LED_BUILTIN = 2;
#define BUILTIN_LED LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN

long now;
long start;

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  initWiFi();
  initTime();
  initFileSystem();
  initWebServer();
  initMPU9250();
  initTempSensors();
  initPulseSensor();
  start = time(&now);
}

long int i = 0;

void loop()
{
  server.handleClient();
  delay(20); // allow the cpu to switch to other tasks
  time(&now);
  if (now - start >= 30)
  {
    printLocalTime();
    statusMPU9250();
    statusTempSensors();
    start = time(&now);
  }
}