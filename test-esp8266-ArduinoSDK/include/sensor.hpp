#ifndef SENSOR_H_
#define SENSOR_H_

#include "shared.hpp"


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
        Sensor(const Sensor&)  = delete;
        Sensor(Sensor&&)       = delete;

        #pragma region Decode - virtual
        /// <summary> 
        /// Takes care of decoding the raw data, passed as 
        /// a byte vector, and formatting it as a string 
        /// </summary> 
        /// <param name="rawData"> The data read from the sensor </param>
        /// <param name="result"> The result, must be set by the method </param>
        virtual void decode(
            SensorData& rawData,
            string&     result
        ) const = 0;
        #pragma endregion

        #pragma region Get id
        /// <summary>
        /// Returns the sensor's ID.
        /// </summary>
        inline byte getId() const
        {
            return this->_id;
        }
        #pragma endregion

        #pragma region Get name
        /// <summary>
        /// Returns the sensor's name.
        /// </summary>
        inline const string& getName() const
        {
            return this->_name;
        }
        #pragma endregion

    protected:
        #pragma region ctor
        /// <summary>
        /// Creates a new Sensor.
        /// This constructor is protected.
        /// </summary>
        ///
        /// <param name="id"> The sensor's id. </param>
        /// <param name="name"> The sensor's name. </param>
        Sensor(
            const byte    id,
            const string& name
        ) :
            _id  (id),
            _name(name) 
        {}
        #pragma endregion

        const byte    _id;
        const string& _name;
    };
}}

#endif // !SENSOR_H_