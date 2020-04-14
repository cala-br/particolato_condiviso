#ifndef SERIAL_CHANNEL_HPP_
#define SERIAL_CHANNEL_HPP_

#include <channel.hpp>
#include <Arduino.h>


namespace cc {
namespace channels {

	class SerialChannel : public Channel
	{
	public:
		SerialChannel() {}

		const SensorData& read()
		{
			_currentData.id = 1;
			auto& data = _currentData.data;

			data.clear();
			string raw = 
				Serial.readStringUntil('\n');

			for (auto c : raw)
				data.push_back(c);

			return _currentData;
		}
	};

}}


#endif // !SERIAL_CHANNEL_HPP_