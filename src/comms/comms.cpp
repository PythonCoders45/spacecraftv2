#include "comms.h"
#include <sstream>

GroundCommand CommsSubsystem::parse_ground_uplink(const std::string& packet_string) {
    std::stringstream ss(packet_string);
    std::string cmd_name;
    double cmd_value = 0.0;

    // Split string by commas (e.g., "SET_ATTITUDE,45.0")
    if (std::getline(ss, cmd_name, ',')) {
        std::string val_str;
        if (std::getline(ss, val_str)) {
            cmd_value = std::stod(val_str);
        }
    }

    GroundCommand cmd;
    if (cmd_name == "SET_ATTITUDE") {
        cmd.type = CMD_SET_TARGET_ATTITUDE;
        cmd.value = cmd_value;
    } else if (cmd_name == "RCS_BOOST") {
        cmd.type = CMD_TRIGGER_RCS_BOOST;
        cmd.value = cmd_value;
    } else {
        cmd.type = CMD_UNKNOWN;
        cmd.value = 0.0;
    }

    return cmd;
}