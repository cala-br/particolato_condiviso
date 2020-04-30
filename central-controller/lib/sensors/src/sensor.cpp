#include <sensor.hpp>


namespace cc {
namespace sensors {

    Sensor::Sensor(
        const byte   id,
        const string name
    ) :
        _id(id),
        _name(name)
    {}


    byte Sensor::getId() const {
        return this->_id;
    }

    const string& Sensor::getName() const {
        return this->_name;
    }

}}