#ifndef I2C_HAL_HPP_
#define I2C_HAL_HPP_

#include <common.hpp>
#include <Wire.h>
#include <array>
#include <vector>


namespace cc {
namespace i2c {


	void beginReadTransaction(
		word slaveAddress,
		byte registerAddress,
		byte bytes
	);


	template <typename Symbol>
	Symbol read();

	template <>
	inline byte read<byte>() {
		return Wire.read();
	}

	template <>
	inline word read<word>() {
		return (
			Wire.read() << 8 | Wire.read()
		);
	}


	template <typename Symbol, byte Size>
	std::array<Symbol, Size> readMultiple()
	{
		std::array<Symbol, Size> res;

		for (byte i = 0; i < Size; i++)
			res[i] = read<Symbol>();
	
		return res;
	}

	template <typename Symbol, byte Size>
	void readMultiple(std::vector<Symbol>& out)
	{
		for (byte i = 0; i < Size; i++)
			out.push_back( read<Symbol>() );
	}


	inline void write(word slaveAddress, word registerAddress)
	{
		Wire.beginTransmission(slaveAddress);
		Wire.write(registerAddress);
		Wire.endTransmission(true);
	}

	template <byte Size>
	void write(word slaveAddress, std::array<byte, Size> data) 
	{
		Wire.beginTransmission(slaveAddress);

		for (byte b : data)
			Wire.write(b);

		Wire.endTransmission(true);
	};

	template <byte Size>
	void write(word slaveAddress, word registerAddress, std::array<byte, Size> data) 
	{
		Wire.beginTransmission(slaveAddress);
		Wire.write(registerAddress);

		for (byte b : data)
			Wire.write(b);

		Wire.endTransmission(true);
	};

}}

#endif // !I2C_HAL_HPP_
