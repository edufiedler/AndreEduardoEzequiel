#include <WebServer.h>
#include <ESPmDNS.h>

#include <WiFi.h>
#include <WiFiClient.h>

#include <time.h>
#include <esp_sntp.h>

#include <SPIFFS.h>
// #include <FS.h>

extern WebServer server;
extern File fsUploadFile;
String formatBytes(size_t bytes);
String getContentType(String filename);
bool exists(String path);
bool handleFileRead(String path);
void handleFileUpload();
void handleFileDelete();
void handleFileCreate();
void handleFileList();

const long gmtOffset_sec = -3 * 3600;    // -3 horas Brasília
const int daylightOffset_sec = 0 * 3600; // sem horário de verão = 0
extern tm timeinfo;

// You only need to format the filesystem once
#define FORMAT_FILESYSTEM false

void initFileSystem();
void initWiFi();
void initTime();
void initWebServer();

void printLocalTime();