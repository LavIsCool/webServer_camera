void sendServer(WiFiClient& client, String type, String data) {
  // Send the HTTP response header
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(type);
  client.println("Connection: close");
  client.println();
  // Send the HTTP response body
  client.println(data);
}

void streamServer(WiFiClient& client, String type, File file) {
  // Send the HTTP response header
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(type);
  client.print("Content-Length: ");
  client.println(file.size());
  client.println("Connection: close");
  client.println();
  // Send the HTTP response body
  uint8_t buffer[512];
  while (file.available()) {
    size_t bytesRead = file.read(buffer, sizeof(buffer));
    client.write(buffer, bytesRead);
  }
}

std::vector<std::pair<String, std::function<void(WiFiClient&)>>> URLS;
String args;

void on(String url, const std::function<void(WiFiClient&)>& handleFunc) {
  URLS.push_back({url, handleFunc});
}

void handleClient(WiFiServer& server) {
  WiFiClient client = server.available();
  if (!client) return;
  String request = client.readStringUntil('\r');
  int firstSpace = request.indexOf(' ');
  int secondSpace = request.indexOf(' ', firstSpace + 1);
  String fullPath = request.substring(firstSpace + 1, secondSpace);
  String req = fullPath;
  args = "";
  int pos = fullPath.indexOf('?');
  if (pos != -1) {
    req = fullPath.substring(0, pos);
    args = fullPath.substring(pos + 1);
  }
  for (auto& item : URLS) {
    String& url = item.first;
    auto& handleFunc = item.second;
    if (req == url) { handleFunc(client); }
  }
  delay(10);
  client.stop();
}