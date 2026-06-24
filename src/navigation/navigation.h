#ifndef NAVIGATION_H
#define NAVIGATION_H

struct OrbitState {
    double position; // Meters from center of Earth
    double velocity; // Meters per second
};

class NavigationSubsystem {
private:
    // Kalman Filter variables
    double estimated_angle; 
    double error_covariance;
    double process_noise;   // Q
    double sensor_noise;    // R

public:
    NavigationSubsystem(double initial_angle);

    // Kalman Filter: Fuses a noisy raw sensor reading with our physics prediction
    double filter_sensor_data(double predicted_angle, double raw_sensor_reading);

    // RK4 Propagator: Solves differential equations for orbital mechanics
    OrbitState propagate_orbit(double pos, double vel, double dt);
};

#endif // NAVIGATION_H