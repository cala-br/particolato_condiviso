#include <sps30.hpp>
#include <i2c_hal.hpp>

using namespace std;


namespace cc {
namespace sensors {

    namespace cmd = Sps30Command;
    namespace par = Sps30Param;
    using readerr = Sps30ReadError;


    Sps30::Sps30() : I2CSensor(0x69, "sps30") {}

    void Sps30::init()
    {

    }

    SensorData Sps30::read() const
    {
        return {};
    }

    string Sps30::decode(const SensorData& data) const
    {
        return "decoded";
    }


    void Sps30::startMeasurement() const
    {
        const byte crc = computeChecksum({
            par::MEASUREMENT_MODE,
            par::DUMMY_BYTE,
        });

        const array<byte, 3> data = {
            par::MEASUREMENT_MODE,
            par::DUMMY_BYTE,
            crc,
        };

        i2c::write<3>(this-> id, cmd::START_MEASUREMENT, data);
    }

    void Sps30::stopMeasurement() const
    {
        i2c::write(this->id, cmd::STOP_MEASUREMENT);
    }

    auto Sps30::hasNewData() const -> Sps30ReadResult<bool>
    {
        const auto res = 
            readDefault(cmd::READ_DATA_READY_FLAG);

        SPS30_HANDLE_ERROR(res.error);

        constexpr byte NEW_DATA_FLAG = 0x01;
        const byte dflag = res.result[1];
        return {
            .result = (dflag == NEW_DATA_FLAG),
            .error  = readerr::NONE,
        };
    }


    auto Sps30::readDefault(word command) const -> Sps30DefaultReadResult
    {
        i2c::beginReadTransaction(
            this->id, 
            command, 
            par::DEFAULT_READ_LEN);

        const auto data = 
            i2c::readMultiple<byte, par::DEFAULT_READ_LEN>();

        const bool isCrcValid = 
            validateChecksum(data);

        if (!isCrcValid)
            return {
                .result = {},
                .error  = readerr::WRONG_CRC,
            };

        return {
            .result = data,
            .error  = readerr::NONE,
        };
    }


    byte Sps30::computeChecksum(const array<byte, 2>& data)
    {
        byte crc = 0xFF;
        for(byte i = 0; i < 2; i++) 
        {
            crc ^= data[i];
            for(byte bit = 8; bit > 0; --bit) 
            {
                if(crc & 0x80) {
                    crc = (crc << 1) ^ 0x31u;
                } else {
                    crc = (crc << 1);
                }
            }
        }
        return crc;
    }

    bool Sps30::validateChecksum(const array<byte, 3>&data)
    {
        const byte b1   = data[0];
        const byte b2   = data[1];
        const byte dcrc = data[2];

        const auto crc = 
            computeChecksum({ b1, b2 });

        return dcrc == crc;
    }

}}