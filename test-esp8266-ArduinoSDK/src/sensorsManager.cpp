#include "sensorsManager.hpp"


namespace cc {
namespace sensors {

    #pragma region Get instance
    /// <summary>
    /// Returns the current instance of the
    /// SensorsManager. 
    /// </summary>
    const SensorsManager& SensorsManager::getInstance()
    {
        static auto instance = std
            ::unique_ptr<SensorsManager>(new SensorsManager);

        return *instance.get();
    }
    #pragma endregion

    #pragma region Get sensor
    /// <summary
    /// Returns the Sensor object associated
    /// to the given id.
    /// </summary>
    ///
    /// <param name="id"> The Sensor's id. </param> 
    const Sensor& SensorsManager::getSensor(byte id) const
    {
        static std::map<
            byte, 
            std::unique_ptr<Sensor>
        > sensorsMap;
        
        return *sensorsMap[id];
    }
    #pragma endregion
}}