#ifndef SENSORS_DISPATCHER_H_
#define SENSORS_DISPATCHER_H_

#include "shared.hpp"
#include "sensor.hpp"
#include <map>
#include <memory>


namespace cc::sensors
{
    class SensorsDispatcher
    {
    public:
        SensorsDispatcher(const SensorsDispatcher&) = delete;
        SensorsDispatcher(SensorsDispatcher&&)      = delete;

        static const 
        SensorsDispatcher& getInstance();

        const Sensor& getSensor(byte id) const;

        #pragma region Dispose
        /**
         * @brief 
         * Disposes of the instantiated sensors.
         */
        inline void dispose()
        {
            for (const auto& pair : _sensorsMap)
                delete pair.second;
        }
        #pragma endregion

    private:
        SensorsDispatcher();

        static std::unique_ptr<
            SensorsDispatcher
        > _instance;

        static std::map<
            byte, 
            Sensor*
        > _sensorsMap;
    };
}

#endif // !SENSORS_DISPATCHER_H_