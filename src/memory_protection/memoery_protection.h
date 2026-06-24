#ifndef MEMORY_PROTECTION_H
#define MEMORY_PROTECTION_H

class MemoryProtection {
public:
    // TMR: Takes three copies of a critical variable and returns the correct voted value
    double triple_modular_voting(double copyA, double copyB, double copyC);

    // ECC: Mimics checking a data byte for bit corruption using parity rules
    uint8_t simulate_radiation_bit_flip(uint8_t original_data, int bit_to_flip);
    uint8_t repair_corrupted_byte(uint8_t raw_byte, uint8_t backup_byte);
};

#endif // MEMORY_PROTECTION_H