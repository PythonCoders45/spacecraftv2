#ifndef COMMS_H
#define COMMS_H

#include <string>

// Definitions of supported Ground Commands
enum CommandType {
    CMD_UNKNOWN,
    CMD_SET_TARGET_ATTITUDE,
    CMD_TRIGGER_RCS_BOOST
};

struct GroundCommand {
    CommandType type;
    double value; // The payload data (e.g., target angle or thrust duration)
};

class CommsSubsystem {
public:
    // Parse a text string sent from Ground Control into a system command packet
    GroundCommand parse_ground_uplink(const std::string& packet_string);
};

#endif // COMMS_H