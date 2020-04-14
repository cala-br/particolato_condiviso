#ifndef I2C_DEVICE_HPP_
#define I2C_DEVICE_HPP_


namespace cc {
namespace devices {
    
    class I2CDevice
    {
    public:
        I2CDevice(
            int registersCount,
            int registersStartAddress
        ) :
            _registersCount(registersCount),
            _registersStartAddress(registersStartAddress)
        {}


        inline int getRegistersCount() { 
            return _registersCount; 
        }

        inline int getRegistersStartAddress() { 
            return _registersStartAddress; 
        }


    private:
        int _registersCount;
        int _registersStartAddress;
    };
}}


#endif // !I2C_DEVICE_HPP