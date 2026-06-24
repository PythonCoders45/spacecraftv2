#include "scheduler.h"

TaskScheduler::TaskScheduler(double time_step) : tick_count(0), dt(time_step) {}

void TaskScheduler::increment_tick() {
    tick_count++;
}

bool TaskScheduler::should_run_adcs() const {
    return true; // Runs every 0.25 seconds (4 Hz)
}

bool TaskScheduler::should_run_power() const {
    return (tick_count % 2 == 0); // Runs every 0.50 seconds (2 Hz)
}

bool TaskScheduler::should_run_comms() const {
    return (tick_count % 4 == 0); // Runs every 1.00 seconds (1 Hz)
}

double TaskScheduler::get_current_time() const {
    return tick_count * dt;
}