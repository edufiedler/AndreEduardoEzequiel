// header com ssid e password
#include "senhadowifidecasa.h"
#include "petDigitalServer.h"

#include <WiFi.h>
#include <WiFiClient.h>

#include <ESPmDNS.h>
#include <time.h>
#include <esp_sntp.h>


// apenas para DOIT ESP32 DEVKIT V1
static const uint8_t LED_BUILTIN = 2;
#define BUILTIN_LED LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN

const char *host = "petdigitalcfa";

/*
possíveis servidores NTP (máx 3):
{"pool.ntp.org","0.pool.ntp.org","1.pool.ntp.org","2.pool.ntp.org","3.pool.ntp.org",
"pool.ntp.br","time.nist.gov","br.pool.ntp.org","a.st1.ntp.br","b.st1.ntp.br","c.st1.ntp.br",}

Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S")
%A - dia da semana, textual, completo (Sunday - Saturday)
%B - mês, textual, completo (January - December)
%Y - ano com 4 dígitos
%m - mês (01-12)
%d - dia do mês (01-31)
%H - hora (00-23)
%M - minuto (00-59)
%S - segundo (00-61)

struct tm
{
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
#ifdef __TM_GMTOFF
  long	__TM_GMTOFF;
#endif
#ifdef __TM_ZONE
  const char *__TM_ZONE;
#endif
};
*/

const char *ntpServers[3] = {
    "time.nist.gov",
    "pool.ntp.org",
    "pool.ntp.br"};

const long gmtOffset_sec = -3 * 3600;    // -3 horas Brasília
const int daylightOffset_sec = 0 * 3600; // sem horário de verão = 0
struct tm timeinfo;

// You only need to format the filesystem once
#define FORMAT_FILESYSTEM false

/*
  init
 */

void initFileSystem()
{
  if (FORMAT_FILESYSTEM)
    SPIFFS.format();
  SPIFFS.begin();
  {
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file)
    {
      String fileName = file.name();
      size_t fileSize = file.size();
      Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
      file = root.openNextFile();
    }
    Serial.printf("\n");
  }
}

void initWiFi()
{
  Serial.printf("Connecting to %s\n", ssid);
  if (String(WiFi.SSID()) != String(ssid))
  {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void initTime()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServers[0], ntpServers[1], ntpServers[2]);
  printLocalTime();
}

void printLocalTime()
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");
}

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.print("\n");
  Serial.setDebugOutput(true);
  initFileSystem();
  initWiFi();
  initTime();

  MDNS.begin(host);
  Serial.print("Open http://");
  Serial.print(host);
  Serial.println(".local/edit to see the file browser");
  // list directory
  server.on("/list", HTTP_GET, handleFileList);
  // load editor
  server.on("/edit", HTTP_GET, []()
            {
    if (!handleFileRead("/edit.htm")) {
      server.send(404, "text/plain", "FileNotFound");
    } });
  // create file
  server.on("/edit", HTTP_PUT, handleFileCreate);
  // delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  // first callback is called after the request has ended with all parsed arguments
  // second callback handles file uploads at that location
  server.on(
      "/edit", HTTP_POST, []()
      { server.send(200, "text/plain", ""); },
      handleFileUpload);

  // called when the url is not defined here
  // use it to load content from FILESYSTEM
  server.onNotFound([]()
                    {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "FileNotFound");
    } });

  // get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, []()
            {
    String json = "{";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ", \"analog\":" + String(analogRead(A0));
    json += ", \"gpio\":" + String((uint32_t)(0));
    json += "}";
    server.send(200, "text/json", json);
    json = String(); });
  server.begin();
  Serial.println("HTTP server started");
}

long int i = 0;

void loop()
{
  server.handleClient();
  delay(2); // allow the cpu to switch to other tasks
}