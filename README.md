# Smart Greenhouse Automation (ESP32)

A smart greenhouse monitor and automation system using ESP32, DHT22 sensor, soil moisture sensor, and MQTT protocol.

## Features
- Read temperature and humidity via DHT22
- Read soil moisture
- Publish data to MQTT (HiveMQ broker)
- Control water pump or fan (LED used as actuator)

## Hardware Required
- ESP32 Dev Module
- DHT22 Temperature and Humidity Sensor
- Soil Moisture Sensor (analog)
- LED or relay module for actuator
- Breadboard + jumper wires

## Setup
1. Install Arduino IDE and ESP32 board manager
2. Install PubSubClient and DHT sensor libraries
3. Replace WiFi credentials in `main.cpp`
4. Upload to ESP32 and monitor via serial

## MQTT Topics
- `greenhouse/temp`
- `greenhouse/hum`
- `greenhouse/soil`

## License
MIT