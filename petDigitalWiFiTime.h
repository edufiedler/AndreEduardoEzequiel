#include <WiFi.h>
#include <esp_sntp.h>
#include <time.h>

const long gmtOffset_sec = -3 * 3600;    // -3 horas Brasília
const int daylightOffset_sec = 0 * 3600; // sem horário de verão = 0
extern tm timeinfo;

void initWiFi();
void initTime();
void printLocalTime();
String getLocalTimeString();