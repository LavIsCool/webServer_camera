#include <WiFi.h>
#include <LittleFS.h>

class CustomServer {
  private:
    std::vector<std::pair<String, std::function<void()>>> URLS;
    std::vector<std::pair<String, String>> ARGS;
    WiFiServer server;
    WiFiClient client;

    void separateArgs(String args) {
      bool run = true;
      String key = "";
      String value = "";
      int pos1;
      int pos2;
      String str = args;
      String temp = "";
      while (run) {
        ARGS.clear();
        pos1 = str.indexOf('&');
        if (pos1 == -1) {
          temp = str;
          run = falsep;
        } else {
          temp = str.substring(0, pos1);
          str = str.substring(pos1+1);
        }
        pos2 = temp.indexOf('=');
        key = temp.substring(0,pos2);
        value = temp.substring(pos2+1);
        ARGS.push_back({key,value});
      }
    }
  public:
    CustomServer(int port) : server(port) {}

    void begin() {server.begin();}

    void send(int code, String type, String data) {
      // Send the HTTP response header
      client.print("HTTP/1.1 ");
      client.println(code);
      client.print("Content-Type: ");
      client.println(type);
      client.println("Connection: close");
      client.println();
      // Send the HTTP response body
      client.println(data);
    }

    void streamFile(int code, String type, File file) {
      // Send the HTTP response header
      client.print("HTTP/1.1 ");
      client.println(code);
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

    void on(String url, const std::function<void()>& handleFunc) {
      URLS.push_back({url, handleFunc});
    }

    bool hasArg(String key) {
      for (auto& arguments : ARGS) {
        String& param = arguments.first;
        if (key == param) return true;
      }
      return false;
    }

    String arg(String key) {
      for (auto& arguments : ARGS) {
        String& param = arguments.first;
        String& value = arguments.second;
        if (key == param) return value;
      }
      return "";
    }

    void handleClient() {
      client = server.available();
      if (!client) return;
      String request = client.readStringUntil('\r');
      int firstSpace = request.indexOf(' ');
      int secondSpace = request.indexOf(' ', firstSpace + 1);
      String fullPath = request.substring(firstSpace + 1, secondSpace);
      String req = fullPath;
      String args = "";
      int pos = fullPath.indexOf('?');
      if (pos != -1) {
        req = fullPath.substring(0, pos);
        args = fullPath.substring(pos + 1);
      }
      separateArgs(args);
      for (auto& item : URLS) {
        String& url = item.first;
        auto& handleFunc = item.second;
        if (req == url) { handleFunc(); }
      }
      delay(10);
      client.stop();
    }
};