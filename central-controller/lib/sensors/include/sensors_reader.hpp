#ifndef SENSORS_READER_HPP_
#define SENSORS_READER_HPP_

#include <channel.hpp>
#include <memory>
#include <thread>

namespace cc {
namespace channels {
	
	class SensorsReader
	{
	public:
		SensorsReader(const SensorsReader&) = delete;
		SensorsReader(SensorsReader&&)		= delete;
		SensorsReader(
			std::vector<std::shared_ptr<Channel>>&& channels);

		void start();


		using SensorDataReceivedHandler = 
			std::function<void(const SensorData&)>;

		/// <summary>
		/// Data received event.
		/// </summary>
		SensorDataReceivedHandler dataReceived;

	private:

		std::vector<
			std::shared_ptr<Channel>> _channels;

		// A thread will be started for each channel.
		std::vector<
			std::unique_ptr<std::thread>> _readingThreads;

		// Friend is used in order to let the thread
		// class access the handleChannel(...) method.
		friend class std::thread;
		static void handleChannel(
			SensorsReader			 *reader,
			std::shared_ptr<Channel>  channel
		);
	};

}}


#endif // !SENSORS_READER_HPP_