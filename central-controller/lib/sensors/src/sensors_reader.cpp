#include <sensors_reader.hpp>

namespace cc {
namespace channels {

	/// <summary>
	/// Creates a new SensorsReader with the given list 
	/// of channels.
	/// </summary>
	SensorsReader::SensorsReader(
		std::vector<std::shared_ptr<Channel>>&& channels)
		:
		_channels(channels)
	{}


	/// <summary>
	/// Creates a separate thread for each channel
	/// and starts reading.
	/// </summary>
	void SensorsReader::start()
	{
		for (auto& channel : _channels)
		{
			_readingThreads.push_back(
				make_unique<std::thread>(
					SensorsReader::handleChannel,
					this,
					channel));
		}
	}


	/// <summary>
	/// Handles a channel, reading and 
	/// generating read events from it.
	/// </summary>
	void SensorsReader::handleChannel(
		SensorsReader			 *reader,
		std::shared_ptr<Channel>  channel
	) {
		SensorData sData;
		while (true)
		{
			sData = channel->read();
			reader->dataReceived(sData);
		}
	}

}}