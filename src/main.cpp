#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define LED_PIN 2
#define SOIL_SENSOR_PIN 34

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Greenhouse")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int soil = analogRead(SOIL_SENSOR_PIN);

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.printf("Temp: %.1f°C, Humidity: %.1f%%, Soil: %d\n", temp, hum, soil);

  char tempStr[8], humStr[8], soilStr[8];
  dtostrf(temp, 6, 2, tempStr);
  dtostrf(hum, 6, 2, humStr);
  sprintf(soilStr, "%d", soil);

  client.publish("greenhouse/temp", tempStr);
  client.publish("greenhouse/hum", humStr);
  client.publish("greenhouse/soil", soilStr);

  digitalWrite(LED_PIN, (soil < 300) ? HIGH : LOW);

  delay(5000);
}