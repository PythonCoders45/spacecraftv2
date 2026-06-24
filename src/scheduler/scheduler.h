#ifndef SCHEDULER_H
#define SCHEDULER_H

class TaskScheduler {
private:
    unsigned long long tick_count;
    double dt;

public:
    TaskScheduler(double time_step);
    
    void increment_tick();
    bool should_run_adcs() const;    // High frequency (Every tick)
    bool should_run_power() const;   // Mid frequency (Every 2 ticks)
    bool should_run_comms() const;   // Low frequency (Every 4 ticks)
    double get_current_time() const;
};

#endif // SCHEDULER_H