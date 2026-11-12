void initWIFI() {
  WiFi.mode(WIFI_AP);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
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

void setLeds() {
  if (RedState) digitalWrite(Red, HIGH); else digitalWrite(Red, LOW);
  if (GreenState) digitalWrite(Green, HIGH); else digitalWrite(Green, LOW);
  if (BlueState) digitalWrite(Blue, HIGH); else digitalWrite(Blue, LOW);
}

void initServer() {
  on("/", handleRoot);
  on("/toggle", handleToggle);
  on("/data", handleData);
  on("/script.js",  [](WiFiClient& client) { handleFile(client, "/script.js", "text/javascript"); });
  on("/style.css",  [](WiFiClient& client) { handleFile(client, "/style.css", "text/css"); });
  on("/Radar.mp4",  [](WiFiClient& client) { handleFile(client, "/Radar.mp4", "video/mp4"); });
  on("/favicon.ico",[](WiFiClient& client) { handleFile(client, "/favicon.ico", "image/x-icon"); });
  server.begin();
}