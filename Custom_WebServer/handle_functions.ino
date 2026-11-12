void handleRoot(WiFiClient& client) {
  File file = LittleFS.open("/esp32.html", "r");
  if (!file) {
    file.close();
    return;
  }
  String html = file.readString();
  file.close();
  sendServer(client, "text/html", html);
}

void handleFile(WiFiClient& client, String file_path, String file_type) {
  File file = LittleFS.open(file_path, "r");
  if (!file) {
    file.close();
    return;
  }
  streamServer(client, file_type, file);
  file.close();
}

void handleToggle(WiFiClient& client) {
  if (args.indexOf("state") != -1) {
    String state = args.substring(args.indexOf('=')+1);
    Serial.println(state);
    if (state == "red") RedState = !RedState;
    if (state == "green") GreenState = !GreenState;
    if (state == "blue") BlueState = !BlueState;
    setLeds();
    sendServer(client, "text/plain", "ok");
  }
}

void handleData(WiFiClient& client) {
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

  sendServer(client, "application/json", json);
}