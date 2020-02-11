#ifndef SENSORS_READER_H_
#define SENSORS_READER_H_

#include "channel.hpp"

namespace cc {
namespace channels {
	
	class SensorsReader
	{
	public:
		SensorsReader(const SensorsReader&) = delete;
		SensorsReader(SensorsReader&&)		= delete;

	private:
		SensorReader();
	};

}}


#endif // !SENSORS_READER_H_