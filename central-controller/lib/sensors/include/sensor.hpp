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
        virtual string decode(const SensorData& rawData) = 0;

        byte          getId()   const;
        const string& getName() const;

    protected:
        Sensor(
            const byte   id,
            const string name
        );

        const byte   _id;
        const string _name;

    public:
        Sensor(const Sensor&&) = delete;
        Sensor(Sensor&)        = delete;
    };
}}

#endif // !SENSOR_HPP_