#ifndef Kalman_h_
#define Kalman_h_

namespace PE
{
class KalmanFilter {
public:
    KalmanFilter();
    KalmanFilter(double var_accel);
    void reset(double abs_value, double vel_value);

    // Updates state given a sensor measurement of the absolute value of x,
    // the variance of that measurement, and the interval since the last
    // measurement in seconds. This interval must be greater than 0; for the
    // first measurement after a reset(), it's safe to use 1.0.
    void update(double z_abs, double var_z_abs, double dt); // The absolute value of x.

    inline double getXAbs() const
    {
        return x_abs_;
    }
    // The rate of change of x.
    inline double getXVel() const
    {
        return x_vel_;
    }

private:
    double x_abs_; // The absolute value of x.
    double x_vel_; // The rate of change of x.

    // Covariance matrix for the state.
    double p_abs_abs_;
    double p_abs_vel_;
    double p_vel_vel_;

    // The variance of the acceleration noise input in the system model.
    double var_accel_;
};
} // namespace PE

#endif