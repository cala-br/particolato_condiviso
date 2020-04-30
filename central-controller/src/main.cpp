#include <Arduino.h>
#include <channels>
#include <sensors>


using namespace cc::channels;
using namespace cc::sensors;


I2CChannel i2c({
    cc::make_shared<Bme280>()
});


void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    Serial.println(i2c.readNext());
}