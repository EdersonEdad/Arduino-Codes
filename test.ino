#include <WiFiManager.h>  
#include <WiFi.h>         

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_AP);  // Force AP mode

    WiFiManager wm;

    // Reset WiFi settings (forces AP mode if connection fails)
    wm.resetSettings();
    delay(1000);

    bool res = wm.autoConnect("ESP32-CAM-WiFi", "12345678");  // AP SSID & Password

    if (!res) {
        Serial.println("⚠️ Failed to connect. Restarting...");
        ESP.restart();
    } else {
        Serial.println("✅ Connected!");

        // Print SSID & Password
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        Serial.print("PASSWORD: ");
        Serial.println(WiFi.psk());

        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
}

void loop() {
    delay(10000);
}
