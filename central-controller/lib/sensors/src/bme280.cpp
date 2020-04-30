#include <bme280.hpp>


namespace cc {
namespace sensors {

	Bme280::Bme280()
		:
		I2CSensor(60, "bme280")
	{}


	SensorData Bme280::read()
	{
		SensorData res;

		res.id   = _id;
		res.data = { 1, 2, 3 };

		return res;
	}


	string Bme280::decode(const SensorData& rawData)
	{
		string res = "{ ";
		
		for (auto ch : rawData.data)
			res += ch + ' ';

		res += "}";
		return res;
	}

}}