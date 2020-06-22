#include <Arduino.h>
#include <channels>
#include <sensors>
#include <AsyncMqttClient.h>
#include <WiFi.h>

using namespace cc::channels;
using namespace cc::sensors;


constexpr char WIFI_SSID[] = "";
constexpr char WIFI_PASS[] = "";

constexpr char MQTT_HOSTNAME[] = "mqtt.ssh.edu.it";
constexpr word MQTT_PORT       = 1883;
constexpr char WEATHER_DATA_TOPIC[] = 
    "calabretti/particolato/weather_data";


I2CChannel i2c;
AsyncMqttClient mqttClient;


void setup() 
{
    i2c.addSensor(cc::make_unique<Bme280>());
    i2c.initAll();

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    mqttClient.setServer(MQTT_HOSTNAME, MQTT_PORT);
    mqttClient.connect();
}


void loop()
{
    const auto data = i2c.readNext();
    mqttClient.publish(
        WEATHER_DATA_TOPIC, 0, false, data.c_str());
    
    delay(1000);
}