#include <bme280.hpp>
#include <i2c_hal.hpp>

using namespace std;


namespace cc {
namespace sensors {

	Bme280::Bme280(const Bme280ID id) 
		: I2CSensor(
			static_cast<byte>(id), "bme280")
	{}


	void Bme280::init()
	{
		i2c::write<6>(this->id,
		{
			Bme280Register::CONFIG,
			0xA0,	// Sampling rate 1 sec

			Bme280Register::CTRL_HUM,
			0x01,

			Bme280Register::CTRL_MEAS,
			0x27,	// Pressure and temperature data acquisition options
		});
		this->_calibrationParams = readCalibrationParams();
	}

	Bme280CalibrationParams Bme280::readCalibrationParams()
	{
		constexpr byte FIRST_REG_LEN  = 26;
		constexpr byte SECOND_REG_LEN = 7;
		constexpr byte TOTAL_BYTES    = FIRST_REG_LEN + SECOND_REG_LEN;
		
		vector<byte> rawParams(TOTAL_BYTES);
		
		// Calib_00
		i2c::beginReadTransaction(
			this->id, 
			Bme280Register::ADDR_CALIB_00, 
			FIRST_REG_LEN);

		i2c::readMultiple<byte, FIRST_REG_LEN>(rawParams);

		// Calib_13
		i2c::beginReadTransaction(
			this->id, 
			Bme280Register::ADDR_CALIB_13, 
			SECOND_REG_LEN);

		i2c::readMultiple<byte, SECOND_REG_LEN>(rawParams);

		return sdtocb(rawParams);
	}
		
	byte Bme280::syncId() const
	{
		i2c::beginReadTransaction(
			this->id, Bme280Register::ID, 1);

		return i2c::read<byte>();
	}


	SensorData Bme280::read() const
	{
		constexpr byte TOTAL_BYTES = 8;
		SensorData res {
			.id   = this->id,
			.data = vector<byte>(TOTAL_BYTES),
		};
		
		i2c::beginReadTransaction(
			this->id, 
			Bme280Register::ADDR_DATA_LOW, 
			TOTAL_BYTES);

		i2c::readMultiple<byte, TOTAL_BYTES>(res.data);
		return res;
	}

	string Bme280::decode(const SensorData& rawData) const
	{
		StaticJsonDocument<JSON_OBJECT_SIZE(4)> doc;

		const auto& data = rawData.data;
		const dword rawTemperature = computeRawTemperature(data);
		const dword rawPressure    = computeRawPressure(data);
		const dword rawHumidity    = computeRawHumidity(data);

		doc["id"] 		   = rawData.id;
		doc["temperature"] = computeTemperature(rawTemperature);
		doc["pressure"]    = computePressure(rawPressure);
		doc["humidity"]    = computeHumidity(rawHumidity);

		char output[56];
		serializeJson(doc, output);
		return string(output);
	}


	int32_t Bme280::computeTemperature(dword adc_T) const
	{
		auto *dig = &_calibrationParams;

		int32_t var1;
		int32_t var2;
		int32_t temperature;
		int32_t temperature_min = -4000;
		int32_t temperature_max = 8500;
		int32_t t_fine;

		var1 = (int32_t)((adc_T / 8)-((int32_t)dig->dig_T1 * 2));
		var1 = (var1 * ((int32_t)dig->dig_T2)) / 2048;
		var2 = (int32_t)((adc_T / 16)-((int32_t)dig->dig_T1));
		var2 = (((var2 * var2) / 4096) * ((int32_t)dig->dig_T3)) / 16384;
		t_fine = var1 + var2;
		temperature = (t_fine * 5 + 128) / 256;
		if (temperature < temperature_min)
		{
			temperature = temperature_min;
		}
		else if (temperature > temperature_max)
		{
			temperature = temperature_max;
		}

		return temperature;
	}

	dword Bme280::computeHumidity(dword adc_H) const
	{
		auto *dig = &_calibrationParams;

		int32_t var1;
		int32_t var2;
		int32_t var3;
		int32_t var4;
		int32_t var5;
		uint32_t humidity;
		uint32_t humidity_max = 102400;

		var1 = dig->t_fine - ((int32_t)76800);
		var2 = (int32_t)(adc_H * 16384);
		var3 = (int32_t)(((int32_t)dig->dig_H4) * 1048576);
		var4 = ((int32_t)dig->dig_H5) * var1;
		var5 = (((var2 - var3) - var4) + (int32_t)16384) / 32768;
		var2 = (var1 * ((int32_t)dig->dig_H6)) / 1024;
		var3 = (var1 * ((int32_t)dig->dig_H3)) / 2048;
		var4 = ((var2 * (var3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
		var2 = ((var4 * ((int32_t)dig->dig_H2)) + 8192) / 16384;
		var3 = var5 * var2;
		var4 = ((var3 / 32768) * (var3 / 32768)) / 128;
		var5 = var3 - ((var4 * ((int32_t)dig->dig_H1)) / 16);
		var5 = (var5 < 0 ? 0 : var5);
		var5 = (var5 > 419430400 ? 419430400 : var5);
		humidity = (uint32_t)(var5 / 4096);
		if (humidity > humidity_max)
		{
			humidity = humidity_max;
		}

		return humidity;
	}
	
	dword Bme280::computePressure(dword adc_P) const
	{
		auto *dig = &_calibrationParams;

		int32_t var1;
		int32_t var2;
		int32_t var3;
		int32_t var4;
		uint32_t var5;
		uint32_t pressure;
		uint32_t pressure_min = 30000;
		uint32_t pressure_max = 110000;

		var1 = (((int32_t)dig->t_fine) / 2) - (int32_t)64000;
		var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((int32_t)dig->dig_P6);
		var2 = var2 + ((var1 * ((int32_t)dig->dig_P5)) * 2);
		var2 = (var2 / 4) + (((int32_t)dig->dig_P4) * 65536);
		var3 = (dig->dig_P3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8;
		var4 = (((int32_t)dig->dig_P2) * var1) / 2;
		var1 = (var3 + var4) / 262144;
		var1 = (((32768 + var1)) * ((int32_t)dig->dig_P1)) / 32768;

		// avoid exception caused by division by zero
		if (var1)
		{
			var5 = (uint32_t)((uint32_t)1048576) - adc_P;
			pressure = ((uint32_t)(var5 - (uint32_t)(var2 / 4096))) * 3125;
			if (pressure < 0x80000000)
			{
				pressure = (pressure << 1) / ((uint32_t)var1);
			}
			else
			{
				pressure = (pressure / (uint32_t)var1) * 2;
			}
			var1 = (((int32_t)dig->dig_P9) * ((int32_t)(((pressure / 8) * (pressure / 8)) / 8192))) / 4096;
			var2 = (((int32_t)(pressure / 4)) * ((int32_t)dig->dig_P8)) / 8192;
			pressure = (uint32_t)((int32_t)pressure + ((var1 + var2 + dig->dig_P7) / 16));
			if (pressure < pressure_min)
			{
				pressure = pressure_min;
			}
			else if (pressure > pressure_max)
			{
				pressure = pressure_max;
			}
		}
		else
		{
			pressure = pressure_min;
		}

		return pressure;
	}


	dword Bme280::computeRawTemperature(const vector<byte>& data) {
		return 
			(((dword) data[3]) << 12) |
			(((dword) data[4]) << 4 ) |
			(((dword) data[5]) >> 4 )
			;
	}

	dword Bme280::computeRawPressure(const vector<byte>& data) {
		return 
			(((dword) data[0]) << 12) |
			(((dword) data[1]) << 4 ) |
			(((dword) data[2]) >> 4 )
			;
	}

	dword Bme280::computeRawHumidity(const vector<byte>& data) {
		return 
			(((dword) data[6]) << 8) |
			( (dword) data[7])
			;
	}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"
	Bme280CalibrationParams Bme280::sdtocb(const vector<byte>& data)
	{
		return {
			.dig_T1 = ((uint16_t) (data[1]))  << 8 | ((word) (data[0])),
			.dig_T2 = ((int16_t)  (data[3]))  << 8 | ((word) (data[2])),
			.dig_T3 = ((int16_t)  (data[5]))  << 8 | ((word) (data[4])),
			.dig_P1 = ((uint16_t) (data[7]))  << 8 | ((word) (data[6])),
			.dig_P2 = ((int16_t)  (data[9]))  << 8 | ((word) (data[8])),
			.dig_P3 = ((int16_t)  (data[11])) << 8 | ((word) (data[10])),
			.dig_P4 = ((int16_t)  (data[13])) << 8 | ((word) (data[12])),
			.dig_P5 = ((int16_t)  (data[15])) << 8 | ((word) (data[14])),
			.dig_P6 = ((int16_t)  (data[17])) << 8 | ((word) (data[16])),
			.dig_P7 = ((int16_t)  (data[19])) << 8 | ((word) (data[18])),
			.dig_P8 = ((int16_t)  (data[21])) << 8 | ((word) (data[20])),
			.dig_P9 = ((int16_t)  (data[23])) << 8 | ((word) (data[22])),
			.dig_H1 = ((uint8_t)  (data[25])),
			.dig_H2 = ((int16_t)  (data[27])) << 8 | ((word) (data[26])),
			.dig_H3 = ((uint8_t)  (data[28])),
			.dig_H4 = ((int16_t)  (data[29])) << 4 | ((word) (0x0f & data[30])),
			.dig_H5 = ((int16_t)  (data[31])) << 4 | ((word) (data[30]>>4)),
			.dig_H6 = ((int8_t)   (data[32])),
		};
	}
#pragma GCC diagnostic pop

}}