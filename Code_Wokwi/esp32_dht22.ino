#include <WiFi.h>
#include "DHTesp.h"
#include "HTTPClient.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String apiKey = "NRKPJKM55MMNXZ6F";   // Write API Key
const String channelID = " 3175189";

const int DHT_PIN = 15;

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // اتصال WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    TempAndHumidity data = dhtSensor.getTempAndHumidity();
   float temp = random(20, 35);   // من 20 إلى 35 درجة
float hum = random(40, 90);    // من 40% إلى 90%


    Serial.println("Temp: " + String(temp, 2) + "°C");
    Serial.println("Humidity: " + String(hum, 1) + "%");
    Serial.println("Sending to ThingSpeak...");
    
    HTTPClient http;
    String url = "http://api.thingspeak.com/update?api_key=" + apiKey +
                 "&field1=" + String(temp) + 
                 "&field2=" + String(hum);

    http.begin(url);
    int httpCode = http.GET();
    http.end();

    Serial.println("ThingSpeak Response: " + String(httpCode));
    Serial.println("---");
  }

  delay(20000);  // كل 20 ثانية (ThinkSpeak يسمح بقراءة كل 15 ثانية)
}
