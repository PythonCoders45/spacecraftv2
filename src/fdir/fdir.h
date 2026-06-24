#ifndef FDIR_H
#define FDIR_H

enum SpacecraftState {
    STATE_NOMINAL,
    STATE_SAFE_MODE
};

class FdirSubsystem {
private:
    int attitude_error_count;
    int critical_fault_threshold;
    SpacecraftState current_state;

public:
    FdirSubsystem();

    // Monitors the system and returns the commanding health state of the vehicle
    SpacecraftState monitor_system_health(double current_angle, double battery_percent);
    
    SpacecraftState get_current_state() const;
};

#endif // FDIR_H