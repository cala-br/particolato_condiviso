#ifndef MOCK_SENSOR_HPP_
#define MOCK_SENSOR_HPP_

#include <sensor.hpp>


namespace cc {
namespace sensors {

	class MockSensor : public Sensor
	{
	public:
		MockSensor() 
			: Sensor(1, "mock_sensor") {}

		void decode(
			const SensorData& rawData,
			string&		      result
		) const
		{
			result = "decoded";
		};
	};

}}


#endif // !MOCK_SENSOR_HPP_