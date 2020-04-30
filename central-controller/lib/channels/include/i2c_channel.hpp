#ifndef I2C_CHANNEL_HPP_
#define I2C_CHANNEL_HPP_

#include <channel.hpp>
#include <comm_info.hpp>


namespace cc {
namespace channels {

	class I2CChannel : public Channel<sensors::I2CSensor>
	{
	public:
		I2CChannel(std::vector<std::shared_ptr<sensors::I2CSensor>> sensors);

		string readNext();
	};

}}

#endif // !I2C_CHANNEL_HPP_