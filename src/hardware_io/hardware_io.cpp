#include "hardware_io.h"
#include <cmath>

HardwareInterface::HardwareInterface() {
    // Zero out our simulated physical hardware memory grid on boot
    for(int i = 0; i < 256; i++) mock_registers[i] = 0x00;
}

void HardwareInterface::write_register(uint8_t reg_address, uint8_t value) {
    mock_registers[reg_address] = value;
}

uint8_t HardwareInterface::read_register(uint8_t reg_address) {
    return mock_registers[reg_address];
}

// --- BIT-MANIPULATION AND COMPRESSION LAW ---
CompressedTelemetry HardwareInterface::pack_telemetry(double angle, double batt, double temp, uint32_t ms) {
    CompressedTelemetry packet;

    // 1. Map float angle (-180.0 to 180.0) into a fixed-point unsigned 16-bit integer
    // This allows us to transmit angles with decimals using raw integer data slots
    double normalized_angle = (angle + 180.0) / 360.0; 
    packet.primary_angle = static_cast<uint16_t>(normalized_angle * 65535.0);

    // 2. Safely cast battery percent to a single byte (0 to 100)
    packet.battery_charge = static_cast<uint8_t>(std::round(batt));

    // 3. Safely cast temperature to a signed 8-bit integer
    packet.temperature = static_cast<int8_t>(std::round(temp));

    // 4. Store standard integer timestamp directly
    packet.timestamp_ms = ms;

    return packet;
}