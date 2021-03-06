#ifndef SHARED_HPP_
#define SHARED_HPP_

#include <Arduino.h>
#include <vector>
#include <memory>

namespace cc
{
    using string = String;
    using byte   = uint8_t;
    using word   = uint16_t;
    using dword  = uint32_t;


    template <typename T, typename ...Args>
    std::shared_ptr<T> make_shared(Args... args)
    {
        return std::shared_ptr<T>(
            new T(std::forward<Args>(args)...));
    }

    template <typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args... args)
    {
        return std::unique_ptr<T>(
            new T(std::forward<Args>(args)...));
    }
}

#endif // !SHARED_HPP_