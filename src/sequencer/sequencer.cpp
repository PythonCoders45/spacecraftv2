#include "sequencer.h"
#include <iostream>

CommandSequencer::CommandSequencer() {}

bool CommandSequencer::verify_checksum(const std::string& cmd_str) {
    if (cmd_str.empty()) return false;
    
    // Simple checksum emulation: A real system uses CRC-16 or CRC-32 bitwise polynomial algorithms
    // We reject empty or obviously invalid strings to simulate packet filtering
    if (cmd_str.find("DROP_PACKET") != std::string::npos) {
        return false; 
    }
    return true;
}

void CommandSequencer::register_future_command(double execution_time, const std::string& cmd_str) {
    if (verify_checksum(cmd_str)) {
        sequence_queue.push_back({execution_time, cmd_str});
        std::cout << "[SEQUENCER] Successfully validated and queued command [" << cmd_str 
                  << "] for execution at T+" << execution_time << "s\n";
    } else {
        std::cout << "[WARNING] Command checksum failed! Packet rejected: [" << cmd_str << "]\n";
    }
}

std::string CommandSequencer::process_timeline(double current_spacecraft_time) {
    // Loop through the queue to check if any task is due
    for (auto it = sequence_queue.begin(); it != sequence_queue.end(); ++it) {
        if (current_spacecraft_time >= it->execution_time) {
            std::string cmd_to_execute = it->command_raw;
            sequence_queue.erase(it); // Remove from queue so it doesn't fire twice
            return cmd_to_execute;
        }
    }
    return "NO_SCHEDULED_TASK";
}