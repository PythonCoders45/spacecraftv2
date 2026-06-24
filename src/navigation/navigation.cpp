#include "navigation.h"
#include <cmath>

// Standard gravitational parameter for Earth (m^3 / s^2)
const double MU_EARTH = 3.986004418e14;

NavigationSubsystem::NavigationSubsystem(double initial_angle) 
    : estimated_angle(initial_angle), error_covariance(1.0), process_noise(0.01), sensor_noise(0.25) {}

// --- FIELD 1: KALMAN FILTER STATE ESTIMATION ---
double NavigationSubsystem::filter_sensor_data(double predicted_angle, double raw_sensor_reading) {
    // 1. Predict Update
    error_covariance += process_noise;

    // 2. Compute Kalman Gain (How much do we trust the sensor vs. our prediction?)
    double kalman_gain = error_covariance / (error_covariance + sensor_noise);

    // 3. Correct Update
    estimated_angle = predicted_angle + kalman_gain * (raw_sensor_reading - predicted_angle);
    error_covariance = (1.0 - kalman_gain) * error_covariance;

    return estimated_angle;
}

// --- FIELD 2: RUNGE-KUTTA 4TH ORDER (RK4) ORBITAL MECHANICS ---
// Auxiliary function to calculate gravitational acceleration: a = -mu / r^2
double get_gravity_accel(double radius) {
    return -MU_EARTH / (radius * radius);
}

OrbitState NavigationSubsystem::propagate_orbit(double pos, double vel, double dt) {
    // k1 steps
    double v_k1 = vel;
    double a_k1 = get_gravity_accel(pos);

    // k2 steps
    double p_k2 = pos + v_k1 * (dt / 2.0);
    double v_k2 = vel + a_k1 * (dt / 2.0);
    double a_k2 = get_gravity_accel(p_k2);

    // k3 steps
    double p_k3 = pos + v_k2 * (dt / 2.0);
    double v_k3 = vel + a_k2 * (dt / 2.0);
    double a_k3 = get_gravity_accel(p_k3);

    // k4 steps
    double p_k4 = pos + v_k3 * dt;
    double v_k4 = vel + a_k3 * dt;
    double a_k4 = get_gravity_accel(p_k4);

    // Weighted RK4 averaging to find the highly precise next state
    double next_pos = pos + (dt / 6.0) * (v_k1 + 2.0 * v_k2 + 2.0 * v_k3 + v_k4);
    double next_vel = vel + (dt / 6.0) * (a_k1 + 2.0 * a_k2 + 2.0 * a_k3 + a_k4);

    return {next_pos, next_vel};
}