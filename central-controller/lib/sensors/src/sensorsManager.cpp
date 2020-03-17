#include <sensorsManager.hpp>

namespace cc {
namespace sensors {

    SensorsManager::SensorsManager(
        std::vector<std::shared_ptr<Sensor>>&& sensors
    ) {
        for (auto& sensor : sensors)
            _sensors.insert({ sensor->getId(), sensor });
    }

}}