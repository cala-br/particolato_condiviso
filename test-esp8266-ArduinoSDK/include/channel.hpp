#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "sensor.hpp"


namespace cc {
namespace channels {

	using sensors::SensorData;

	class Channel
	{
	public:
		Channel(const Channel&) = delete;
		Channel(Channel&&)      = delete;

		virtual const SensorData& read() = 0;

		#pragma region Get current data
		/// <summary>
		/// Returns the data from the last reading.
		/// </summary>
		inline const SensorData& getCurrentData() {
			return this->_currentData;
		}
		#pragma endregion

	protected:
		Channel() {};

		SensorData _currentData;
	};

}}


#endif // !CHANNEL_H_