#ifndef POWER_H
#define POWER_H

struct PowerTelemetry {
    double battery_percent;
    double battery_temp;
    bool heater_status;
    bool in_eclipse;
};

class PowerSubsystem {
private:
    double battery_capacity_wh;
    double current_energy_wh;
    double battery_temp_c;
    bool heater_on;

public:
    PowerSubsystem(double capacity_wh, double initial_temp);
    
    // Process power generation, consumption, and thermal characteristics
    PowerTelemetry update_power_state(bool in_eclipse, double dt);
};

#endif // POWER_H