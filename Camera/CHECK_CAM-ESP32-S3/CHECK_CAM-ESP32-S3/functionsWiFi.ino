//============== functionsWiFi =============
void connectToWifi() {
  IPAddress local_IP(192, 168, 4, 50);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(1000);
  }
  Serial.print("Connected\nIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
}
//=========================================
/*
  Serial.println("Starting WiFi Access Point...");
  Serial.print("AP SSID: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress ip = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(ip);
*/