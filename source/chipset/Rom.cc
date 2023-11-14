// File: Rom.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// ROM interface

// Implementation header
#include "Rom.h"

// C++ library headers
#include <fstream>  // std::ifstream
#include <iterator> // std::istream_iterator

// Project includes
#include "Log.h"

Rom::Rom(std::shared_ptr<Device::SystemBus> systemBus_)
  : Device(systemBus_)
{
    DEBUG("ROM initialised");
}

void Rom::DoTick()
{
    if (systemBus->abortMemoryAccess)
    {
        return;
    }
    if (systemBus->enableROM)
    {
        if (Device::SystemBus::ByteWord::BYTE == systemBus->byteWord)
        {
            if (auto byte = ReadByte(systemBus->addressBus))
            {
                // The CPU is only requesting a byte out of memory
                // but the data bus is a full 32 bits wide. Mask the
                // byte onto a uint32_t with a value of 0 so the
                // behaviour is completely explicit
                uint32_t memoryValue{0};
                memoryValue &= byte.value();
                systemBus->dataBus = memoryValue;
            }
            else
            {
                throw std::runtime_error("Illegal memory access attempted");
            }
        }
        else
        {
            if (auto word = ReadWord(systemBus->addressBus))
            {
                systemBus->dataBus = word.value();
            }
            else
            {
                throw std::runtime_error("Illegal memory access attempted");
            }
        }
    }
}

bool Rom::Load(std::string& romFilePath)
{
    std::ifstream infile(romFilePath, std::ios_base::binary);
    if (!infile)
    {
        ERROR("Failed to open ROM file: ", romFilePath);
        return false;
    }
    infile.unsetf(std::ios::skipws);

    // Calculate required size allocation
    std::streampos fileSize;
    infile.seekg(0, std::ios::end);
    fileSize = infile.tellg();
    infile.seekg(0, std::ios::beg);

    // Reset ROM content and pack it with content
    // from file stream
    DEBUG("Attempting to load ", fileSize, " bytes from ", romFilePath);
    rom.clear();
    rom.reserve(fileSize);
    rom.insert(rom.begin(),
               std::istream_iterator<uint8_t>(infile),
               std::istream_iterator<uint8_t>());
    if (0 == rom.size() || rom.size() != static_cast<size_t>(fileSize))
    {
        ERROR("Failed to load ROM file contents: ", romFilePath);
        return false;
    }

    INFO("Successfully loaded ROM file: ", romFilePath, ", ", rom.size(), " bytes");
    return true;
}

std::optional<uint8_t> Rom::ReadByte(uint32_t address)
{
    try
    {
        return rom.at(address);
    }
    catch(std::out_of_range&)
    {
        ERROR("Failed to read ROM, address out of range: ", address);
    }
    return std::nullopt;
}

std::optional<uint32_t> Rom::ReadWord(uint32_t address)
{
    uint32_t word{0};
    int bytesRead{0};

    for (bytesRead = 0; bytesRead < 4; bytesRead++)
    {
        try
        {
            word |= (rom.at(address) << bytesRead);
        }
        catch(std::out_of_range&)
        {
            ERROR("Failed to read ROM, address out of range: ", address);
        }
    }

    if (bytesRead == 3) return word;
    return std::nullopt;
}

Rom::~Rom()
{
    DEBUG("ROM uninitialised");
}
