#ifndef SENSOR_H_
#define SENSOR_H_

#include "shared.hpp"


namespace cc::sensors
{
    class Sensor
    {
    public:
        Sensor()               = delete;
        Sensor(const Sensor&)  = delete;
        Sensor(Sensor&&)       = delete;

        virtual void decode(
            ByteVect rawData,
            string&  result
        ) const = 0;

        #pragma region Get id
        /**
         * @brief Returns the sensor's ID.
         */
        inline byte getId() const
        {
            return this->_id;
        }
        #pragma endregion

        #pragma region Get name
        /**
         * @brief Returns the sensor's name.
         */
        inline const string& getName() const
        {
            return this->_name;
        }
        #pragma endregion

    protected:
        #pragma region ctor
        /**
         * @brief 
         * Creates a new Sensor.
         * This constructor is protected.
         * 
         * @param id   The sensor's id.
         * @param name The sensor's name.
         */
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
}

#endif // !SENSOR_H_