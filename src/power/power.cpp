#include "power.h"

PowerSubsystem::PowerSubsystem(double capacity_wh, double initial_temp)
    : battery_capacity_wh(capacity_wh), current_energy_wh(capacity_wh * 0.8), // Start at 80% charge
      battery_temp_c(initial_temp), heater_on(false) {}

PowerTelemetry PowerSubsystem::update_power_state(bool in_eclipse, double dt) {
    // Base power draw of flight computer and reaction wheels (Watts)
    double power_consumption = 15.0; 
    double power_generation = 0.0;

    if (!in_eclipse) {
        power_generation = 40.0; // Solar panels generating 40 Watts in sunlight
    }

    // If battery is freezing (below 0°C), turn on the 10W survival heater
    if (battery_temp_c < 0.0) {
        heater_on = true;
    } else if (battery_temp_c > 5.0) {
        heater_on = false; // Turn off once safe
    }

    if (heater_on) {
        power_consumption += 10.0; // Heater consumes extra power
        battery_temp_c += 1.2 * dt; // Heater warms up the battery
    } else {
        // Space is cold; passive thermal radiation cools the battery down
        battery_temp_c -= 0.5 * dt; 
    }

    // Net power calculation (Watts * Hours = Watt-hours)
    double net_power_w = power_generation - power_consumption;
    current_energy_wh += (net_power_w * (dt / 3600.0)); // Convert dt seconds to hours

    // Bounds checking for battery capacity
    if (current_energy_wh > battery_capacity_wh) current_energy_wh = battery_capacity_wh;
    if (current_energy_wh < 0.0) current_energy_wh = 0.0;

    double soc_percent = (current_energy_wh / battery_capacity_wh) * 100.0;

    return {soc_percent, battery_temp_c, heater_on, in_eclipse};
}