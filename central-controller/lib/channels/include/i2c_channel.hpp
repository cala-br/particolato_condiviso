#ifndef I2C_CHANNEL_HPP_
#define I2C_CHANNEL_HPP_

#include <channel.hpp>
#include <comm_info.hpp>


namespace cc {
namespace channels {

	class I2CChannel : public Channel
	{
	public:
		I2CChannel(
			int delay,
			int timeout,
			std::vector<std::shared_ptr<sensors::Sensor>> sensors
		);

		string readNext();
	};

}}

#endif // !I2C_CHANNEL_HPP_