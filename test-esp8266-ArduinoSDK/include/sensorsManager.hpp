#ifndef SENSORS_MANAGER_H_
#define SENSORS_MANAGER_H_

#include "shared.hpp"
#include "sensor.hpp"
#include <map>
#include <memory>


namespace cc {
namespace sensors {

    template <class ...SensorTypes>
    class SensorsManager
    {
    public:
        SensorsManager(const SensorsManager&) = delete;
        SensorsManager(SensorsManager&&)      = delete;

        //const Sensor& getSensor(byte id) const;

        SensorsManager(SensorTypes... sensorTypes) 
        {
            
        };

    private:
        std::vector<
            std::unique_ptr<Sensor>> _sensors;
    };
}}

#endif // !SENSORS_DISPATCHER_H_