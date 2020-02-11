#ifndef SENSORS_MANAGER_H_
#define SENSORS_MANAGER_H_

#include "shared.hpp"
#include "sensor.hpp"
#include <map>
#include <memory>


namespace cc {
namespace sensors {

    class SensorsManager
    {
    public:
        SensorsManager(const SensorsManager&) = delete;
        SensorsManager(SensorsManager&&)      = delete;

        static const 
            SensorsManager& getInstance();

        const Sensor& getSensor(byte id) const;

    private:
        SensorsManager() {};
    };
}}

#endif // !SENSORS_DISPATCHER_H_