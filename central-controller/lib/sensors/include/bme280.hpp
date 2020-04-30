#ifndef BME280_HPP_
#define BME280_HPP_

#include <comm_info.hpp>


namespace cc {
namespace sensors {

	class Bme280 : public I2CSensor
	{
	public:
		Bme280();

		SensorData read();
		string	   decode(const SensorData&);
	};
}}


#endif // !BME280_HPP_