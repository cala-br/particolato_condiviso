#ifndef SENSOR_HPP_
#define SENSOR_HPP_

#include <common.hpp>


namespace cc {
namespace sensors {

    struct SensorData
    {
        byte              id;
        std::vector<byte> data;
    };


    class Sensor
    {
    public:

        /// <summary> 
        /// Takes care of decoding the raw data, passed as 
        /// a byte vector, and formatting it as a string 
        /// </summary> 
        /// <param name="rawData"> The data read from the sensor </param>
        virtual string decode(const SensorData& rawData) const = 0;
        virtual void   init() = 0;

        const byte   id;
        const string name;

    protected:
        Sensor(
            const byte   id,
            const string name
        ) :
            id(id),
            name(name)
        {};
    };
}}

#endif // !SENSOR_HPP_