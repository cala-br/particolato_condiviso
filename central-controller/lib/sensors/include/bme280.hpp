#ifndef BME280_HPP_
#define BME280_HPP_

#include <comm_info.hpp>
#include <arduino_json.hpp>


namespace cc {
namespace sensors {

	struct Bme280CalibrationParams
	{
		uint16_t dig_T1;
		int16_t  dig_T2;
		int16_t  dig_T3;
		uint16_t dig_P1;
		int16_t  dig_P2;
		int16_t  dig_P3;
		int16_t  dig_P4;
		int16_t  dig_P5;
		int16_t  dig_P6;
		int16_t  dig_P7;
		int16_t  dig_P8;
		int16_t  dig_P9;
		uint8_t  dig_H1;
		int16_t  dig_H2;
		uint8_t  dig_H3;
		int16_t  dig_H4;
		int16_t  dig_H5;
		int8_t   dig_H6;
		int32_t  t_fine;
	};

	class Bme280 : public I2CSensor
	{
	public:
		Bme280();

		void init();
		byte syncId() const;

		auto read()					   const -> SensorData;
		auto decode(const SensorData&) const -> string;

		int32_t computeTemperature(dword rawTemperature) const;
		dword 	computePressure   (dword rawPressure)    const;
		dword 	computeHumidity   (dword rawHumidity)    const;

		static dword computeRawTemperature(const std::vector<byte>& data);
		static dword computeRawPressure   (const std::vector<byte>& data);
		static dword computeRawHumidity   (const std::vector<byte>& data);
		static auto  sdtocb(const std::vector<byte>& data) -> Bme280CalibrationParams;

	private:
		Bme280CalibrationParams _calibrationParams;

		auto readCalibrationParams() -> Bme280CalibrationParams;
	};

	struct Bme280Register {
		enum _Bme280Register : byte
		{
			ID = 0xD0,

			CTRL_HUM  = 0xF2,
			CTRL_MEAS = 0xF4,

			CONFIG = 0xF5,

			ADDR_DATA_LOW = 0xF7,
			ADDR_CALIB_00 = 0x88,
			ADDR_CALIB_13 = 0xE1,
		};
	};
}}


#endif // !BME280_HPP_