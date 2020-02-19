#ifndef SENSORS_READER_H_
#define SENSORS_READER_H_

#include "channel.hpp"
#include <memory>
#include <thread>

namespace cc {
namespace channels {
	
	class SensorsReader
	{
	public:
		SensorsReader(const SensorsReader&) = delete;
		SensorsReader(SensorsReader&&)		= delete;

		#pragma region ctor
		/// <summary>
		/// Creates a new SensorsReader with the given list 
		/// of channels.
		/// </summary>
		SensorsReader(
			std::vector<
				std::shared_ptr<Channel>> channels)
			:
			_channels(channels)
		{}
		#pragma endregion


		using SensorDataReceivedHandler = 
			std::function<void(const SensorData&)>;

		/// <summary>
		/// Data received event.
		/// </summary>
		SensorDataReceivedHandler dataReceived;

	private:

		std::vector<
			std::shared_ptr<Channel>> _channels;

		/// <summary>
		/// A thread will be executed for each channel.
		/// </summary>
		std::vector<
			std::unique_ptr<std::thread>> _readingThreads;
	};

}}


#endif // !SENSORS_READER_H_