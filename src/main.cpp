#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(921600);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin("YourWiFiSSID", "YourWiFiPassword");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Scan for nearby devices
  int networkCount = WiFi.scanNetworks();
  Serial.println("Scan complete!");

  // Print the details of each device
  for (int i = 0; i < networkCount; i++) {
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
    Serial.print("Signal strength (RSSI): ");
    Serial.println(WiFi.RSSI(i));
    Serial.println("-------------------------");
  }
}

void loop() {
  // Your code here (if any)
}