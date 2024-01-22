#include <WebServer.h>
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