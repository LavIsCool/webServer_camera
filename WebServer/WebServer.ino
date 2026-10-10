#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <Adafruit_AHTX0.h>
const char* ssid = "Vaismannew";
const char* password = "015666456";

WebServer server(80);
Adafruit_AHTX0 aht;

#define Red 26
#define Green 27
#define Blue 2

double temperature = 0;
double humidity = 0;

bool RedState = false;
bool GreenState = false;
bool BlueState = false;

void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(1000);
  }
  Serial.print("Connected\nIP: ");
  Serial.println(WiFi.localIP());
}

void initAht() {
  if (!aht.begin()) {
  Serial.println("Could not find AHT? Check wiring");
  while (1) delay(10);
  }
}

void initPins() {
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  setLeds();
}

void initServer() {
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/data", handleData);
  server.on("/script.js",  []() { handleFile("/script.js", "text/javascript"); });
  server.on("/style.css",  []() { handleFile("/style.css", "text/css"); });
  server.on("/Radar.mp4",  []() { handleFile("/Radar.mp4", "video/mp4"); });
  server.on("/favicon.ico",[]() { handleFile("/favicon.ico", "image/x-icon"); });
  server.begin();
}

void handleRoot() {
  File file = LittleFS.open("/esp32.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Storage Error: esp32.html not found.");
    file.close();
    return;
  }
  server.send(200, "text/html", file);
}

void handleFile(String file_path, String file_type) {
  File file = LittleFS.open(file_path, "r");
  if (file) {
    server.sendHeader("Cache-Control", "public, max-age=86400");
    server.streamFile(file, file_type);
    file.close();
  } else { 
    server.send(404, "text/plain", file_path + " not found");
  }
}

void handleToggle() {
  if (server.hasArg("state")) {
    String state = server.arg("state");
    if (state == "red") RedState = !RedState;
    if (state == "green") GreenState = !GreenState;
    if (state == "blue") BlueState = !BlueState;
    setLeds();
    server.send(200, "text/plain", "ok");
  }
}

void setLeds() {
  if (RedState) digitalWrite(Red, HIGH); else digitalWrite(Red, LOW);
  if (GreenState) digitalWrite(Green, HIGH); else digitalWrite(Green, LOW);
  if (BlueState) digitalWrite(Blue, HIGH); else digitalWrite(Blue, LOW);
}

void handleData() {
  String json = "{";
  json += R"("temperature":)";
  json += String(temperature);
  json += R"(,"humidity":)";
  json += String(humidity);
  json += R"(,"red":)";
  json += RedState;
  json += R"(,"green":)";
  json += GreenState;
  json += R"(,"blue":)";
  json += BlueState;
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  if(!LittleFS.begin(true)){
    Serial.println("An Error occurred while mounting LittleFS");
    return;
  }
  initWifi();
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
