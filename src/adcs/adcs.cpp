#include "adcs.h"

// Constructor for the Controller
FlightController::FlightController(double p, double i, double d) 
    : kp(p), ki(i), kd(d), integral(0.0), previous_error(0.0), first_run(true) {}

// Discrete PID Algorithm
double FlightController::calculate_command(double target, double current, double dt) {
    double error = target - current;
    
    // Proportional
    double P_out = kp * error;

    // Integral
    integral += error * dt;
    double I_out = ki * integral;

    // Derivative
    double derivative = 0.0;
    if (!first_run && dt > 0.0) {
        derivative = (error - previous_error) / dt;
    }
    double D_out = kd * derivative;

    first_run = false;
    previous_error = error;

    return P_out + I_out + D_out;
}

// Constructor for Spacecraft Physical Properties
SpacecraftDynamics::SpacecraftDynamics(double initial_angle, double moment_of_inertia) 
    : angle(initial_angle), velocity(0.0), inertia(moment_of_inertia) {}

// Physics Simulation Engine (Semi-Implicit Euler)
void SpacecraftDynamics::update_physics(double commanded_torque, double dt) {
    double acceleration = commanded_torque / inertia;
    velocity += acceleration * dt;
    angle += velocity * dt;
}