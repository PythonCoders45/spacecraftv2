#ifndef ADCS_H
#define ADCS_H

// Telemetry structure for downlinking data to Earth
struct TelemetryData {
    double timestamp;      
    double current_angle;  
    double angular_vel;    
    double control_effort; 
};

// PID Flight Controller Class
class FlightController {
private:
    double kp, ki, kd;
    double integral;
    double previous_error;
    bool first_run;

public:
    FlightController(double p, double i, double d);
    double calculate_command(double target, double current, double dt);
};

// Spacecraft Dynamics Simulator Class
class SpacecraftDynamics {
public:
    double angle;       
    double velocity;    
    double inertia;     

    SpacecraftDynamics(double initial_angle, double moment_of_inertia);
    void update_physics(double commanded_torque, double dt);
};

#endif // ADCS_H