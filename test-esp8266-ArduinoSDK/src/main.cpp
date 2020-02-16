#include <Arduino.h>
#include "sensorsReader.hpp"
#include "mockChannel.hpp"

using namespace cc::channels;


void setup() 
{
    
}

void loop() 
{
    static SensorsReader reader(
    {
        std::shared_ptr<MockChannel>()
    });
    
    const auto& sData = 
        reader[0]->read();


}