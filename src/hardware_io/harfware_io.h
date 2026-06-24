#ifndef HARDWARE_IO_H
#define HARDWARE_IO_H

#include <cstdint>

// A professional binary packet format to compress satellite data over a radio link
// Total size: Exactly 8 bytes (64 bits) total instead of massive text strings!
struct CompressedTelemetry {
    uint16_t primary_angle;  // 16 bits: Scaled representation of the attitude angle
    uint8_t  battery_charge; // 8 bits: Direct 0-100 percentage
    int8_t   temperature;    // 8 bits: Signed integer for temperature (-128 to 127 C)
    uint32_t timestamp_ms;   // 32 bits: Monotonic milliseconds since system boot
};

class HardwareInterface {
private:
    uint8_t mock_registers[256]; // Simulated internal memory layout of an IMU chip

public:
    HardwareInterface();

    // Emulate writing and reading raw bytes to a physical sensor over SPI/I2C
    void write_register(uint8_t reg_address, uint8_t value);
    uint8_t read_register(uint8_t reg_address);

    // Bit-Packing: Compresses raw floating point data into a compact binary frame
    CompressedTelemetry pack_telemetry(double angle, double batt, double temp, uint32_t ms);
};

#endif // HARDWARE_IO_H