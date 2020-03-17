#include <Arduino.h>
#include <channels>
#include <sensors>


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
    Serial.begin(9600);

    reader.dataReceived = [](const SensorData& sData)
    {
        cc::string res;
        manager
            .getSensor(sData.id)
            .decode(sData, res);

        Serial.println(res);
    };

    reader.start();
}

void loop() 
{

}