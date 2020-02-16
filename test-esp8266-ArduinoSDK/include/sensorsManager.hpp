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

        SensorsManager(
            std::vector<std::shared_ptr<Sensor>> sensors
        )
        {
            for (auto& sensor : sensors)
                _sensors.insert({ sensor->getId(), sensor });
        };

        const Sensor& getSensor(byte id) {
            return *_sensors[id];
        };

        const Sensor& operator[](byte id) {
            return getSensor(id);
        }

    private:
        std::map<
            byte,
            std::shared_ptr<Sensor>
        > _sensors;
    };
}}

#endif // !SENSORS_DISPATCHER_H_