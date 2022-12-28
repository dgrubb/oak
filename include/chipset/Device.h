// File: Device.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a base class describing common properties of A3000's
// chipset devices which can be derived by specific chips.

#ifndef DEVICE_H
#define DEVICE_H

// C++ library includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

class Device
{
public:

    // Archimedes/ARM2 address bus is only 26-bits wide. A uint32_t
    // is used for convenience so this mask is used to access only the
    // bits which should actually be utilised.
    static constexpr uint32_t AddressBusMask = 0x0FFFFFFF;
    struct SystemBus
    {
        typedef bool RW;

        // This is oriented towards to the CPU's perspective of its output
        // signal. In other words, when WRITE then the CPU is writing which may
        // be a read from the perspective of the device being written to
        enum ReadWrite
        {
            READ = 0,
            WRITE
        };

        uint32_t addressBus{0};
        uint32_t dataBus{0};
        RW rw{READ};
    };

    Device(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Device();

protected:

    uint32_t GetAddressBus();
    uint32_t GetDataBus();
    SystemBus::RW GetReadWrite();

    void SetAddressBus(uint32_t addr);
    void SetDataBus(uint32_t data);
    void SetReadWrite(SystemBus::RW direction);

    void Tick();

private:

    std::shared_ptr<Device::SystemBus> systemBus;

    virtual void DoTick() = 0;
};

#endif // DEVICE_H
