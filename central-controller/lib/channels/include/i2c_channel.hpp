#ifndef I2C_CHANNEL_HPP_
#define I2C_CHANNEL_HPP_

#include <channel.hpp>

namespace cc {
namespace channels {

	class I2CChannel : public Channel
	{
	public:
		I2CChannel() {}
		
		inline const SensorData& read() {
			return this->_currentData;
		}
	};

}}

#endif // !I2C_CHANNEL_HPP_