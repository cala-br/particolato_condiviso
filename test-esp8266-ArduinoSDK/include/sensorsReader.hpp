#ifndef SENSORS_READER_H_
#define SENSORS_READER_H_

#include "channel.hpp"
#include <memory>

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

		#pragma region Get sensor
		/// <summary>
		/// Access the channel stored at the given index.
		/// </summary>
		inline std::shared_ptr<Channel> operator [](byte index){
			return _channels[index];
		}
		#pragma endregion

	private:
		std::vector<
			std::shared_ptr<Channel>> _channels;
	};

}}


#endif // !SENSORS_READER_H_