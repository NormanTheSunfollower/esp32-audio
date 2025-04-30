#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

#define I2S_DOUT  25
#define I2S_BCLK  27
#define I2S_LRC   26

Audio audio;

String ssid = "Amath wifi2.4G";
String password = "0897220796";

bool isPlaying = false;

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();  // ลบช่องว่างหรือ \n

    if (cmd == "green" && !isPlaying) {
      isPlaying = true;
      Serial.println("Playing GREEN sound...");
      audio.connecttohost("https://normanthesunfollower.github.io/esp32-audio/green.mp3");

    } else if (cmd == "red" && !isPlaying) {
      isPlaying = true;
      Serial.println("Playing RED sound...");
      audio.connecttohost("https://normanthesunfollower.github.io/esp32-audio/red.mp3");  

    } else if (cmd == "yellow" && !isPlaying) {
      isPlaying = true;
      Serial.println("Playing YELLOW sound...");
      audio.connecttohost("https://normanthesunfollower.github.io/esp32-audio/yellow.mp3"); 
    }
  }

  if (isPlaying) {
    audio.loop();

    if (!audio.isRunning()) {
      isPlaying = false;
      Serial.println("Finished playing.");
    }
  }
}
