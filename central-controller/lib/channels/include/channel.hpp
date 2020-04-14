#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include <sensor.hpp>


namespace cc {
namespace channels {

	using sensors::SensorData;

	class Channel
	{
	public:
		Channel(const Channel&) = delete;
		Channel(Channel&&)      = delete;

		virtual const SensorData& read() = 0;

		
		/// <summary>
		/// Returns the data from the last reading.
		/// </summary>
		inline const SensorData& getCurrentData() {
			return this->_currentData;
		}
		

	protected:
		Channel() {};

		SensorData _currentData;
	};

}}


#endif // !CHANNEL_HPP_