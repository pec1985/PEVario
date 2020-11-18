#include "KalmanFilter.hpp"

PE::KalmanFilter::KalmanFilter()
{
    x_abs_ = 0.0;
    x_vel_ = 0.0;
    p_abs_abs_ = 0.0;
    p_abs_vel_ = 0.0;
    p_vel_vel_ = 0.0;
    var_accel_ = 1.0;
    reset(0.0, 0.0);
}
PE::KalmanFilter::KalmanFilter(double var_accel)
{
    x_abs_ = 0.0;
    x_vel_ = 0.0;
    p_abs_abs_ = 0.0;
    p_abs_vel_ = 0.0;
    p_vel_vel_ = 0.0;
    var_accel_ = var_accel;
    reset(0.0, 0.0);
}
void PE::KalmanFilter::reset(double abs_value, double vel_value)
{
    x_abs_ = abs_value;
    x_vel_ = vel_value;
    p_abs_abs_ = 1.e10;
    p_abs_vel_ = 0.0;
    p_vel_vel_ = var_accel_;
}

// Updates state given a sensor measurement of the absolute value of x,
// the variance of that measurement, and the interval since the last
// measurement in seconds. This interval must be greater than 0; for the
// first measurement after a reset(), it's safe to use 1.0.
void PE::KalmanFilter::update(double z_abs, double var_z_abs, double dt)
{
    // Note: math is not optimized by hand. Let the compiler sort it out.
    // Predict step.
    // Update state estimate.
    x_abs_ += x_vel_ * dt;
    // Update state covariance. The last term mixes in acceleration noise.
    p_abs_abs_ += 2. * dt * p_abs_vel_ + dt * dt * p_vel_vel_ + var_accel_ * dt * dt * dt * dt / 4.;
    p_abs_vel_ += dt * p_vel_vel_ + var_accel_ * dt * dt * dt / 2.;
    p_vel_vel_ += +var_accel_ * dt * dt;

    // Update step.
    double y = z_abs - x_abs_; // Innovation.
    double s_inv = 1. / (p_abs_abs_ + var_z_abs); // Innovation precision.
    double k_abs = p_abs_abs_ * s_inv; // Kalman gain
    double k_vel = p_abs_vel_ * s_inv;
    // Update state estimate.
    x_abs_ += k_abs * y;
    x_vel_ += k_vel * y;
    // Update state covariance.
    p_vel_vel_ -= p_abs_vel_ * k_vel;
    p_abs_vel_ -= p_abs_vel_ * k_abs;
    p_abs_abs_ -= p_abs_abs_ * k_abs;
}
