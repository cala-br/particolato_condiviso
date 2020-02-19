#include <Arduino.h>
#include "sensorsReader.hpp"
#include "sensorsManager.hpp"
#include "channels"
#include "sensors"


using namespace cc::channels;
using namespace cc::sensors;


static SensorsReader reader({
    cc::make_shared<MockChannel>()
});

static SensorsManager manager({
    cc::make_shared<MockSensor>()
});


void setup() 
{
    Serial.begin(115200);

    reader.dataReceived = [](const SensorData& sData)
    {
        cc::string res;
        manager
            .getSensor(sData.id)
            .decode(sData, res);

        Serial.println(res);
    };
}

void loop() 
{

}