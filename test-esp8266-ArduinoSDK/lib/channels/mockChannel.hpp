#ifndef SERIAL_CHANNEL_H_
#define SERIAL_CHANNEL_H_

#include "channel.hpp"
#include <Arduino.h>


namespace cc {
namespace channels {

	class MockChannel : public Channel
	{
	public:
		MockChannel() {}

		const SensorData& read()
		{
			_currentData.id = 1;
			auto& cd = _currentData.data;

			cd.clear();
			for (auto c : "hello")
				cd.push_back(c);

			return _currentData;
		}
	};

}}


#endif // !SERIAL_CHANNEL_H_