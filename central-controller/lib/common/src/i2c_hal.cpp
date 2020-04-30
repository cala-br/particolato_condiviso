#include <i2c_hal.hpp>


namespace cc {
namespace i2c {

	void beginTransaction(
		word slaveAddress,
		byte registerAddress,
		byte bytes
	) {
		Wire.beginTransmission(slaveAddress);
		Wire.write(registerAddress);

		Wire.endTransmission(false);
		Wire.requestFrom(
			slaveAddress, bytes, true);
	}

}}