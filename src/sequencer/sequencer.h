#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <string>
#include <vector>

struct TimeTaggedCommand {
    double execution_time;    // Simulation time when this command should fire
    std::string command_raw;  // The raw string payload (e.g., "SET_ATTITUDE,90.0")
};

class CommandSequencer {
private:
    std::vector<TimeTaggedCommand> sequence_queue;

    // Aerospace Security: A simple checksum to make sure the command wasn't corrupted in transit
    bool verify_checksum(const std::string& cmd_str);

public:
    CommandSequencer();
    
    // Load a validated command into our timeline queue
    void register_future_command(double execution_time, const std::string& cmd_str);
    
    // Checks if any command in the queue matches the current spacecraft clock time
    std::string process_timeline(double current_spacecraft_time);
};

#endif // SEQUENCER_H