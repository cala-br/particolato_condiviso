# MQTT Topics

The topics used when transmitting
 Topic | Description
 ----- | -----------
 `controllers/sensors/{sensorId}/` | Contains the data published by a sensor 

# Transmission format

A json string with the following fields
```json
{
    "sensorName": "bme280",     // string
    "sensorId"  : 60,           // number
    "sensorData": {             // any
        "temperature": 20,
        "pressure"   : 999000 
    } 
}
```