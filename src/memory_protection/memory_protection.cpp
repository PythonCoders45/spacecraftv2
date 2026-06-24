#include "memory_protection.h"
#include <iostream>

double MemoryProtection::triple_modular_voting(double copyA, double copyB, double copyC) {
    // If all match, everything is nominal
    if (copyA == copyB && copyB == copyC) {
        return copyA;
    }
    
    // If one memory register got corrupted by radiation, the majority rules
    std::cout << "[RADIATION DETECTED] TMR Warning: Memory desynchronization. ";
    if (copyA == copyB) {
        std::cout << "Voting system isolated Copy C (Value: " << copyC << "). Repairing registry.\n";
        return copyA;
    } else if (copyA == copyC) {
        std::cout << "Voting system isolated Copy B (Value: " << copyB << "). Repairing registry.\n";
        return copyA;
    } else {
        std::cout << "Voting system isolated Copy A (Value: " << copyA << "). Repairing registry.\n";
        return copyB;
    }
}

uint8_t MemoryProtection::simulate_radiation_bit_flip(uint8_t original_data, int bit_to_flip) {
    // Uses the XOR bit operator to flip a specific bit from 0 to 1, or 1 to 0
    return original_data ^ (1 << bit_to_flip);
}

uint8_t MemoryProtection::repair_corrupted_byte(uint8_t raw_byte, uint8_t backup_byte) {
    if (raw_byte != backup_byte) {
        std::cout << "[ECC CORRECTION] Bit mismatch detected on hardware bus! Overwriting corrupted memory with parity backup.\n";
        return backup_byte; 
    }
    return raw_byte;
}