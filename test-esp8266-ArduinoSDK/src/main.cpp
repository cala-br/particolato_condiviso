#include <Arduino.h>
#include "sensorsReader.hpp"
#include "sensorsManager.hpp"
#include "channels"
#include "sensors"

using namespace cc::channels;
using namespace cc::sensors;


void setup() 
{
    
}

void loop() 
{
    static SensorsReader reader({
        std::shared_ptr<MockChannel>()
    });

    static SensorsManager manager({
        std::shared_ptr<MockSensor>()
    });
    
    const auto& sData = 
        reader[0]->read();

    cc::string res;
    manager
        .getSensor(sData.id)
        .decode(sData, res);

    Serial.println(res);
}