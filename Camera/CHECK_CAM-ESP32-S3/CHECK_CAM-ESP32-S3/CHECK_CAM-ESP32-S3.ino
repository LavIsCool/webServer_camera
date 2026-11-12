#include <WiFi.h>
#include <WebServer.h>
#include "esp_camera.h"
#include "esp_http_server.h"

const char* ssid = "Lavi_is_webserver";
const char* password = "webserver";

WebServer server(80);
httpd_handle_t stream_httpd = NULL;

//========== PROTOTYPES ==========
void connectToWifi();
void setupServer();
void sendResponse();
void startCamera();
void startCameraServer();
esp_err_t stream_handler(httpd_req_t *req);

//================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  connectToWifi();
  startCamera();

  setupServer();
  server.begin();

  Serial.println("System Ready");
}

void loop() {
  server.handleClient();
}