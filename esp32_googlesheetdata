
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

const char* ssid = "IOT-RMUTI";
// เปลี่ยนชื่อไวไฟ
const char* password = "@1111111111111!";
// เปลี่ยนรหัสไวไฟ
const char* googleScriptURL = "https://script.google.com/macros/s/AKfycbx0hX0KEzQdd9VE0cpzKfrkNa3jwMH6v9OBiRKUJpUWZgYPLilCJgFfP9kUvliLaA4M/exec";  //ใส่ url appscript ของตัวเอง xxxxxxx

#define DHTPIN D5  //ขา data dht22
#define DHTTYPE DHT22

// DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure client;

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

int randomvalue(int min, int max) {
  int value = rand() % (max - min + 1) + min;
  return value;
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  // dht.begin();
  client.setInsecure();  // ข้ามการตรวจสอบ SSL
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();

  int temperature = randomvalue(1, 30);
  int humidity = randomvalue(1, 30);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT sensor!");
    delay(5000);
    return;
  }

  String url = String(googleScriptURL) + "?temp=" + String(temperature) + "&humi=" + String(humidity);
  Serial.println("Sending: " + url);

  if (client.connect("script.google.com", 443)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: script.google.com\r\n" + "Connection: close\r\n\r\n");

    while (client.connected()) {
      if (client.readStringUntil('\n') == "\r") break;
    }

    Serial.println("Response: " + client.readString());
    client.stop();
  } else {
    Serial.println("Connection failed!");
  }

  delay(2000);  // ส่งข้อมูลทุก 2 วินาที
}
