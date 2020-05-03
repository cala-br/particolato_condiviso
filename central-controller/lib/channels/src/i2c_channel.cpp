#include <i2c_channel.hpp>

using namespace std;
using namespace cc::sensors;


namespace cc {
namespace channels {

	I2CChannel::I2CChannel(
		int delay,
		int timeout,
		vector<shared_ptr<Sensor>> sensors
	) :
		Channel(delay, timeout, sensors)
	{}


	string I2CChannel::readNext()
	{
		auto sensor = 
			static_pointer_cast<I2CSensor>(this->getNext());

		auto data = sensor->read();
		return sensor->decode(data);
	}

}}