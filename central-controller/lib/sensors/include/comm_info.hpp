#ifndef COMM_INFO_HPP_
#define COMM_INFO_HPP_

#include <sensor.hpp>


namespace cc {
namespace sensors {

	class I2CSensor : public Sensor
	{
	public:
		virtual SensorData read() const = 0;

	protected:
		I2CSensor(
			const byte id,
			const string name
		) : Sensor(id, name) {}
	};


	class MockSensor : public Sensor 
	{
	public:
		virtual SensorData test() = 0;

	protected:
		MockSensor(
			const byte	 id,
			const string name
		) : Sensor(id, name) {}
	};

}}


#endif // !COMM_INFO_HPP_