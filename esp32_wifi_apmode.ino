#include <WiFi.h>
#include <WiFiManager.h>
#include <Ticker.h>

#define LED 4
#define RESET 5
bool status = true;

Ticker ledBlinker;

void toggleLed() {
  digitalWrite(LED, !digitalRead(LED));
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.print("Connect to AP: ");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
  ledBlinker.attach(0.5, toggleLed);
}

void setup() {
  WiFiManager wm;
  pinMode(RESET, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  Serial.println("Starting WiFiManager with Reset Button...");
  if (digitalRead(RESET) == LOW) {
    Serial.println("Reset button pressed... waiting 3 seconds to confirm.");
    delay(3000); // กันการกดโดยไม่ตั้งใจ

    if (digitalRead(RESET) == LOW) {
      Serial.println("Button held for 3 seconds -> Resetting WiFi settings!");
      wm.resetSettings();   // ล้างค่าการเชื่อมต่อ Wi-Fi เดิม
      delay(1000);
      ESP.restart();        // รีสตาร์ตเครื่อง
    } else {
      Serial.println("Button released -> No reset.");
    }
  }

  wm.setAPCallback(configModeCallback);
  bool res = wm.autoConnect("ESP32-SetupAP", "12345678"); // ชื่อ AP และรหัส

  if (!res) {
    Serial.println("Failed to connect. Restarting...");
    ledBlinker.detach();
    ESP.restart();
  } else {
    Serial.println("WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    ledBlinker.detach();
    digitalWrite(LED, LOW);
  }
}

void loop() {
}
