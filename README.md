# Transmission format

A json string with the following fields
```json
{
    "sensorName": "bme280",
    "sensorId"  : 60,
    "sensorData": {
        "temperature": 20,
        "pressure"   : 999000 
    } 
}
```

The `sensorData` field will contain all the fields relative to the sensor.
