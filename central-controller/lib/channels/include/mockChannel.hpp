#ifndef MOCK_CHANNEL_H_
#define MOCK_CHANNEL_H_

#include <channel.hpp>
#include <Arduino.h>


namespace cc {
namespace channels {

	class MockChannel : public Channel
	{
	public:
		MockChannel() {}

		const SensorData& read()
		{
			delay(1000);

			_currentData.id = 1;
			auto& cd = _currentData.data;

			cd.clear();
			for (auto c : "hello")
				cd.push_back(c);

			return _currentData;
		}
	};

}}


#endif // !MOCK_CHANNEL_H_