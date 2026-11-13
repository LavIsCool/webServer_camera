void handleRoot() {
  File file = LittleFS.open("/esp32.html", "r");
  if (!file) {
    file.close();
    server.send(404, "text/plain", "esp.html not found");
    return;
  }
  String html = file.readString();
  file.close();
  server.send(200, "text/html", html);
}

void handleFile(String file_path, String file_type) {
  File file = LittleFS.open(file_path, "r");
  if (!file) {
    file.close();
    server.send(404, "text/plain", file_path + "not found");
    return;
  }
  server.streamFile(200, file_type, file);
  file.close();
}

void handleToggle() {
  if (server.hasArg("state")) {
    String state = server.arg("state");
    Serial.println(state);
    if (state == "red") RedState = !RedState;
    if (state == "green") GreenState = !GreenState;
    if (state == "blue") BlueState = !BlueState;
    setLeds();
    server.send(200, "text/plain", "ok");
  }
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