#include <WiFi.h>
#include <LittleFS.h>
#include <Adafruit_AHTX0.h>
#include "CustomServer.h"
const char* ssid = "Lavi_is_webserver";
const char* password = "webserver";

CustomServer server(80);
Adafruit_AHTX0 aht;

#define Red 26
#define Green 27
#define Blue 2

double temperature = 0;
double humidity = 0;

bool RedState = false;
bool GreenState = false;
bool BlueState = false;

void setup() {
  Serial.begin(115200);
  if(!LittleFS.begin(true)){
    Serial.println("An Error occurred while mounting LittleFS");
    return;
  }
  initWIFI();
  initServer();
  initAht();
  initPins();
}

void loop() {
  server.handleClient();
  sensors_event_t hum, temp;
  aht.getEvent(&hum, &temp);
  temperature = temp.temperature;
  humidity = hum.relative_humidity;
  delay(100);
}
