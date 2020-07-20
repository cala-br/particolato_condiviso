#include <Arduino.h>
#include <channels>
#include <sensors>
#include <AsyncMqttClient.h>
#include <WiFi.h>
#include <thread>
#include <mutex>

using namespace cc::channels;
using namespace cc::sensors;


constexpr char WIFI_SSID[] = "";
constexpr char WIFI_PASS[] = "";

constexpr char MQTT_HOSTNAME[] = "mqtt.ssh.edu.it";
constexpr word MQTT_PORT       = 1883;
constexpr char WEATHER_DATA_TOPIC[] = "/particolato/weather_data";


I2CChannel      i2c;
AsyncMqttClient mqttClient;
std::mutex      mqttLock;


void mqttSend(const char *topic, const cc::string& data);
void readI2C();

void setup()
{
    i2c.addSensor(cc::make_unique<Bme280>(Bme280ID::ZERO_x76));
    i2c.addSensor(cc::make_unique<Sps30>());
    i2c.initAll();

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    mqttClient.setServer(MQTT_HOSTNAME, MQTT_PORT);
    mqttClient.connect();

    const auto i2cThread = std::thread([] {
        while (true) readI2C();
    });
}


void loop() {}

void readI2C()
{
    const auto data = i2c.readNext();

    mqttSend(WEATHER_DATA_TOPIC, data);
    delay(1000);
}


void mqttSend(const char *topic, const cc::string& data)
{
    mqttLock.lock();
    mqttClient.publish(
        topic, 0, false, data.c_str());

    mqttLock.unlock();
}
