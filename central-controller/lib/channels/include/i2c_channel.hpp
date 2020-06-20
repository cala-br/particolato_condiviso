#ifndef I2C_CHANNEL_HPP_
#define I2C_CHANNEL_HPP_

#include <channel.hpp>
#include <comm_info.hpp>


namespace cc {
namespace channels {

	class I2CChannel : public Channel<sensors::I2CSensor>
	{
	public:
		I2CChannel(
			const int delay,
			const int timeout,
			std::vector<std::unique_ptr<sensors::I2CSensor>> sensors
		) :
			Channel(delay, timeout, move(sensors))
		{}

		I2CChannel(
			const int delay,
			const int timeout
		) : 
			Channel(delay, timeout, {})
		{}

		string readNext();
	};


	string I2CChannel::readNext()
	{
		const auto sensor = this->getNext();

		auto data = sensor->read();
		return sensor->decode(data);
	}

}}

#endif // !I2C_CHANNEL_HPP_