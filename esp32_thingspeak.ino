#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>

#define LED_PIN 15
#define RESET_PIN 0   // ขา GPIO ที่ต่อกับปุ่ม Reset Wi-Fi (เช่น GPIO0)
String apiKey = "ZOIGHSSAS0AGJLAZ"; //แก้เป็นของตัวเอง
const char* server = "http://api.thingspeak.com/update";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStarting...");

  pinMode(LED_PIN, OUTPUT);
  pinMode(RESET_PIN, INPUT_PULLUP);  // เปิด pull-up ภายใน

  WiFiManager wm;

  // ตรวจสอบว่ามีการกดปุ่ม Reset Wi-Fi หรือไม่
  if (digitalRead(RESET_PIN) == LOW) {
    Serial.println("WiFi Reset Button Pressed!");
    wm.resetSettings();          // ล้างข้อมูล Wi-Fi เดิม
    delay(1000);
    ESP.restart();               // รีสตาร์ตเครื่อง
  }

  // เริ่มเชื่อมต่อ Wi-Fi โดยอัตโนมัติ
  bool res = wm.autoConnect("ESP32-WEAP", "11112222");

  if (!res) {
    Serial.println("Failed to connect. Restarting...");
    ESP.restart();
  } else {
    Serial.println("WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // จำลองข้อมูล Sensor
    float temperature = random(25, 35);
    float humidity = random(50, 80);

    String url = server + String("?api_key=") + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity);

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("Data sent to ThingSpeak!");
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
    } else {
      Serial.println("Error sending data.");
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }

  delay(5000); // ThingSpeak จำกัดให้ส่งข้อมูลทุก 15 วินาทีขึ้นไป
}


