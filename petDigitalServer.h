#include <WebServer.h>
#include <ESPmDNS.h>

#include <FS.h>
#define FILESYSTEM SPIFFS
// You only need to format the filesystem once
#define FORMAT_FILESYSTEM true

#if FILESYSTEM == FFat
#include <FFat.h>
#endif
#if FILESYSTEM == SPIFFS
#include <SPIFFS.h>
#endif
#if FILESYSTEM == LittleFS
#include <LittleFS.h>
#endif

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

void initFileSystem();
void initWebServer();