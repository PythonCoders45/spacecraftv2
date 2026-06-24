#include "fdir.h"
#include <iostream>

FdirSubsystem::FdirSubsystem() 
    : attitude_error_count(0), critical_fault_threshold(3), current_state(STATE_NOMINAL) {}

SpacecraftState FdirSubsystem::monitor_system_health(double current_angle, double battery_percent) {
    if (current_state == STATE_SAFE_MODE) {
        return STATE_SAFE_MODE; // Stay in Safe Mode until ground overrides
    }

    bool fault_detected = false;

    // Check 1: Critical Under-Voltage Fault
    if (battery_percent < 15.0) {
        std::cout << "[FDIR ALERT] CRITICAL FAULT: Battery dropped below 15%! Immediate Safe Mode triggered.\n";
        current_state = STATE_SAFE_MODE;
        return current_state;
    }

    // Check 2: Attitude Deviation Fault (Uncontrolled spin or tumbling)
    if (current_angle > 60.0 || current_angle < -60.0) {
        attitude_error_count++;
        std::cout << "[FDIR WARNING] Attitude anomaly detected! Persisting count: " 
                  << attitude_error_count << "/" << critical_fault_threshold << "\n";
        fault_detected = true;
    } else {
        if (attitude_error_count > 0) attitude_error_count--; // De-bounce error count if it stabilizes
    }

    // If a fault persists past our threshold, isolate and recover
    if (attitude_error_count >= critical_fault_threshold) {
        std::cout << "[FDIR CRITICAL] Attitude error threshold breached! Tripping Recovery Action.\n";
        std::cout << "[FDIR RECOVERY] Disabling scientific instruments. Powering down payload. Activating Safe Mode.\n";
        current_state = STATE_SAFE_MODE;
    }

    return current_state;
}

SpacecraftState FdirSubsystem::get_current_state() const {
    return current_state;
}