#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include <sensor.hpp>
#include <functional>
#include <type_traits>


namespace cc {
namespace channels {

	template <typename SensorType>
	class Channel 
	{
	public:
		virtual string readNext() = 0;

		void addSensor	 (std::unique_ptr<SensorType>&& sensor);
		void removeSensor(const byte id);

		void initAll() const;

	protected:
		explicit Channel(std::vector<std::unique_ptr<SensorType>> sensors);
		explicit Channel() 
			: Channel(std::vector<std::unique_ptr<SensorType>>{}) {}

		SensorType* getNext();

		std::vector<
			std::unique_ptr<SensorType>
		> _sensors;

	public:
		Channel(const Channel&&) = delete;
		Channel(Channel&)		 = delete;
	};


	template <typename SensorType>
	Channel<SensorType>::Channel(
		std::vector<std::unique_ptr<SensorType>> sensors
	) :
		_sensors(move(sensors))
	{
		static_assert(
			std::is_base_of<sensors::Sensor, SensorType>::value,
			"`SensorType` must be derived from `Sensor`");
	}


	template <typename SensorType>
	void Channel<SensorType>::addSensor(std::unique_ptr<SensorType>&& sensor)
	{
		_sensors.push_back(move(sensor));
	}


	template <typename SensorType>
	void Channel<SensorType>::removeSensor(const byte id)
	{
		const auto predicate = [id](std::unique_ptr<SensorType>& sensor) {
			return sensor->getId() == id;
		};

		auto el = find_if(
			begin(_sensors),
			end(_sensors),
			predicate);

		if (!*el) return;

		_sensors.erase(el);
	}


	template <typename SensorType>
	SensorType* Channel<SensorType>::getNext()
	{
		static byte i = -1;
		return _sensors[++i %= _sensors.size()].get();
	}


	template <typename SensorType>
	void Channel<SensorType>::initAll() const
	{
		for (auto& sensor : _sensors)
			sensor->init();
	}

}}


#endif // !CHANNEL_HPP_