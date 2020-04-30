#ifndef I2C_HAL_HPP_
#define I2C_HAL_HPP_

#include <common.hpp>
#include <Wire.h>
#include <array>


namespace cc {
namespace i2c {

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
	void readMultiple(std::array<Symbol, Size>& result)
	{
		for (byte i = 0; i < Size; i++)
			result[i] = read<Symbol>();
	}


	void beginTransaction(
		word slaveAddress,
		byte registerAddress,
		byte bytes
	);

}}

#endif // !I2C_HAL_HPP_
