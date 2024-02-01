#include "petDigitalServer.h"
#include "petDigitalMotionTracker.h"
#include "petDigitalTempSensors.h"
#include "petDigitalPulseSensor.h"
#include "petDigitalWiFiTime.h"
//#include "petDigitalState.h"

// apenas para DOIT ESP32 DEVKIT V1
static const uint8_t LED_BUILTIN = 2;
#define BUILTIN_LED LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN

long now;
long start;
long before;
long interval = 1;

File logFile;
String logFilePath;

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
  //initState();
  statusMPU9250();
  start = time(&now);
  //before = start;
  Serial.println(getLocalTimeString());
  logFilePath = "/" + getLocalTimeString() + ".txt";
  logFile = FILESYSTEM.open(logFilePath, FILE_APPEND);
  logFile.print(getLocalTimeString() + " " + statusTempSensors());
}

long int i = 0;

void loop()
{
  server.handleClient();
  delay(20); // allow the cpu to switch to other tasks
  time(&now);
  if (now - start >= 60 * 15) // 15 minutos
  {
    Serial.println(getLocalTimeString());
    statusMPU9250();
    statusTempSensors();
    start = time(&now);
  }
  /*Função de tempo, nao descomentar sem antes integrar 
  parte do servidor com codigo de tempo 

  if(now - before > interval){
    before = now;
    randomState();
  }
  */

}