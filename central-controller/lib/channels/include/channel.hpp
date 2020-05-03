#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include <sensor.hpp>


namespace cc {
namespace channels {

	class Channel
	{
	public:
		virtual string readNext() = 0;

	protected:
		Channel(
			int delay, 
			int timeout, 
			std::vector<std::shared_ptr<sensors::Sensor>> sensors
		);

		std::shared_ptr<sensors::Sensor> getNext();


		int _delay;
		int _timeout;

		std::vector<
			std::shared_ptr<sensors::Sensor>
		> _sensors;

	public:
		Channel(const Channel&&) = delete;
		Channel(Channel&)		 = delete;
	};

}}


#endif // !CHANNEL_HPP_