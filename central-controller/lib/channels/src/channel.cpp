#include <channel.hpp>

using namespace std;
using namespace cc::sensors;


namespace cc {
namespace channels {

	Channel::Channel(
		int delay,
		int timeout,
		vector<shared_ptr<Sensor>> sensors
	) :
		_delay(delay),
		_timeout(timeout),
		_sensors(sensors)
	{}


	shared_ptr<Sensor> Channel::getNext()
	{
		static byte i = -1;
		return _sensors[++i %= _sensors.size()];
	}

}}