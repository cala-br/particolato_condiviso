#ifndef BME280_HPP_
#define BME280_HPP_

#include <sensor.hpp>
#include <i2c_device.hpp>


namespace cc {
namespace sensors {

	class Bme280 : 
		public Sensor, 
		public devices::I2CDevice
	{ 
	public:
		Bme280() : 
			Sensor(60, "bme280"),
			I2CDevice(1, 0x1) 
		{}

		void decode(
			const SensorData& rawData,
			string&			  result
		) const
		{
			result = "decoded";
		};
	};

}}


#endif // !BME280_HPP_