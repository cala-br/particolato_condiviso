#include "includes/sensorsDispatcher.hpp"


namespace cc::sensors
{
    #pragma region Static fields

    std::unique_ptr<
        SensorsDispatcher
    > SensorsDispatcher::_instance = {};
   
    std::map<
        byte, 
        Sensor*
    > _sensorsMap = {};

    #pragma endregion


    #pragma region ctor
    SensorsDispatcher::SensorsDispatcher()
    {

    }
    #pragma endregion


    #pragma region Get instance
    /**
     * @brief 
     * Returns the current instance of the
     * SensorsDispatcher. 
     */
    const SensorsDispatcher& SensorsDispatcher::getInstance()
    {
        if (!_instance)
        {
            _instance = std
                ::unique_ptr<SensorsDispatcher>(new SensorsDispatcher);
        }

        return *_instance.get();
    }
    #pragma endregion

    #pragma region Get sensor
    /**
     * @brief 
     * Returns the Sensor object associated
     * to the given id.
     * 
     * @param id The id of the Sensor. 
     */
    inline const Sensor& SensorsDispatcher::getSensor(byte id) const
    {
        return *_sensorsMap[id];
    }
    #pragma endregion
}