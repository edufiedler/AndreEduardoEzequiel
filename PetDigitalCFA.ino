#include "petDigitalServer.h"
#include "petDigitalWiFiTime.h"
#include "petDigitalState.h"

// apenas para DOIT ESP32 DEVKIT V1
static const uint8_t LED_BUILTIN = 2;
#define BUILTIN_LED LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN

long now;
long start;
long before;
long interval = 10;

File logFile;
String logFilePath;

bool logFileAppendMessage (String msg){
  logFile = FILESYSTEM.open(logFilePath, FILE_APPEND);
  logFile.print(getLocalTimeString() + " " + msg);
  logFile.close();
  return true;
}


void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  initWiFi();
  initTime();
  initFileSystem();
  initWebServer();

  initState();
  
  statusMPU9250();
  start = time(&now);
  before = start;
  Serial.println(getLocalTimeString());
  logFilePath = "/" + getLocalTimeString() + ".txt";
  logFileAppendMessage(statusTempSensors());
  logFileAppendMessage(statusPulseSensor());
}

long int i = 0;

void loop()
{
  server.handleClient();
  delay(100); // se o servidor não responder aumente o valor do delay
  time(&now);
  if (now - start >= 5)
  {
    Serial.println(getLocalTimeString());
    start = time(&now);
  }

  if (now - before > interval)
  {
    before = now;
    randomState();
  }
}