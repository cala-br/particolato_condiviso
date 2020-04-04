# MQTT Topics

The topics used when transmitting
| Topic | Description |
| ----- | ----------- |
| `controllers/{controller}/sensors/{sensorId}/` | Contains the data published by a sensor | 
| `controllers/{controller}/info/`               | Contains the data  |

# Transmission format

A json string with the following fields
```json
Centralina
{
    "id" : 1,
    "lat": "",
    "lon": ""
}

BME
{   
    "idCentralina": 1, 
    "timestamp"   : "",
    "temperature" : 20,
    "pressure"    : 999000,
    "humidity"    : 100 
}
```
