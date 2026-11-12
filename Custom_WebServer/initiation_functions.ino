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
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/data", handleData);
  server.on("/script.js",  []() { handleFile("/script.js", "text/javascript"); });
  server.on("/style.css",  []() { handleFile("/style.css", "text/css"); });
  server.on("/Radar.mp4",  []() { handleFile("/Radar.mp4", "video/mp4"); });
  server.on("/favicon.ico",[]() { handleFile("/favicon.ico", "image/x-icon"); });
  server.begin();
}