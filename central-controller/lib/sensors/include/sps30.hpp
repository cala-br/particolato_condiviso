#ifndef SPS30_HPP_
#define SPS30_HPP_

#include <comm_info.hpp>
#include <array>


namespace cc {
namespace sensors {

    namespace Sps30Command {
        enum _Sps30Command : word
        {
            START_MEASUREMENT         = 0x0010,
            STOP_MEASUREMENT          = 0x0104,
            READ_DATA_READY_FLAG      = 0x0202,
            READ_MEASURED_VALUES      = 0x0300,
            RW_AUTO_CLEANING_INTERVAL = 0x8004,
            START_FAN_CLEANING        = 0x5607,
            READ_ARTICLE_CODE         = 0xD025,
            READ_SERIAL_NUMBER        = 0xD033,
            RESET                     = 0xD304,
        };
    };

    namespace Sps30Param {
        enum _Sps30Param : byte
        {
            DUMMY_BYTE       = 0x00,
            DEFAULT_READ_LEN = 3,

            MEASUREMENT_MODE = 0x03,
        };
    };


    enum class Sps30ReadError
    {
        NONE = 0x00,
        TIMEOUT,
        WRONG_CRC,
    };

    template <typename ResultType>
    struct Sps30ReadResult
    {
        ResultType     result;
        Sps30ReadError error;
    };

    using Sps30DefaultReadResult = 
        Sps30ReadResult<std::array<byte, Sps30Param::DEFAULT_READ_LEN>>;


    class Sps30 : public I2CSensor
    {
    public:
		Sps30();

		void init();
		
		auto read()					   const -> SensorData;
		auto decode(const SensorData&) const -> string;


        void startMeasurement() const;
        void stopMeasurement()  const;
        auto hasNewData()       const -> Sps30ReadResult<bool>;

    private:

        auto readDefault(word command) const -> Sps30DefaultReadResult;

        static byte computeChecksum (const std::array<byte, 2>& data);
        static bool validateChecksum(const std::array<byte, 3>& data);
    };


#define SPS30_HANDLE_ERROR(err) \
    do {                        \
        if (err != Sps30ReadError::NONE) {   \
            return {                         \
                .result = {},                \
                .error  = err,               \
            };                               \
        }                                    \
    } while (false) 

}}


#endif // !SPS30_HPP_