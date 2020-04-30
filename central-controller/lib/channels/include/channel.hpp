#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include <sensor.hpp>


namespace cc {
namespace channels {

	template <typename ST>
	class Channel
	{
	public:
		virtual string readNext() = 0;

	protected:
		Channel(std::vector<std::shared_ptr<ST>> sensors);

		std::vector<
			std::shared_ptr<ST>
		> _sensors;

		std::shared_ptr<ST> getNext();

	public:
		Channel(const Channel&&) = delete;
		Channel(Channel&)		 = delete;
	};


	template <typename ST>
	Channel<ST>::Channel(std::vector<std::shared_ptr<ST>> sensors)
		:
		_sensors(sensors)
	{}


	template <typename ST>
	std::shared_ptr<ST> Channel<ST>::getNext()
	{
		static byte i = -1;
		return _sensors[++i %= _sensors.size()];
	}

}}


#endif // !CHANNEL_HPP_