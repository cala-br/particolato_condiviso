#include <i2c_channel.hpp>

using namespace std;
using namespace cc::sensors;


namespace cc {
namespace channels {

	I2CChannel::I2CChannel(vector<shared_ptr<I2CSensor>> sensors)
		:
		Channel(sensors)
	{}


	string I2CChannel::readNext()
	{
		auto sensor = this->getNext();
		auto data   = sensor->read();

		return sensor->decode(data);
	}

}}