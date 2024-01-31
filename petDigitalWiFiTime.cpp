#include "petDigitalWiFiTime.h"

// header com ssid e password
#include "senhadowifidecasa.h"

/*
possíveis servidores NTP (máx 3):
{"pool.ntp.org","0.pool.ntp.org","1.pool.ntp.org","2.pool.ntp.org","3.pool.ntp.org",
"pool.ntp.br","time.nist.gov","br.pool.ntp.org","a.st1.ntp.br","b.st1.ntp.br","c.st1.ntp.br",}
*/
const char *ntpServers[3] = {
    "time.nist.gov",
    "pool.ntp.org",
    "pool.ntp.br"};

/*
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
struct tm timeinfo;

char timeString[20];

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
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void printLocalTime()
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%Y-%m-%d_%H:%M:%S");
}

void initTime()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServers[0], ntpServers[1], ntpServers[2]);
}

String getLocalTimeString()
{
  
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return "Failed to obtain time";
  }
  strftime(timeString, 20, "%Y-%m-%d_%H:%M:%S", &timeinfo);
  return timeString;
}