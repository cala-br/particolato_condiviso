#include <Arduino.h>
#include "sensorsManager.hpp"

using cc::sensors::SensorsManager;


void setup() 
{
    
}

void loop() 
{
    static const SensorsManager& 
        sm = SensorsManager::getInstance();
}