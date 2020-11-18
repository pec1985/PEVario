#include "Beeper.hpp"
#include "PiecewiseLinearFunction.hpp"

#ifndef NULL
#define NULL 0
#endif

#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif

#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623157e+308
#endif

PE::Beeper::Beeper()
{
    m_sinking = false;
    m_beeping = false;
    m_climbing = false;
    m_var = 0.0;
    m_base = 1000.0;
    m_increment = 100.0;
    m_sinkBase = 500.0;
    m_sinkIncrement = 100.0;
    m_climbThreshold = 0.1; // 20 FPM
    m_sinkThreshold = -2.0; // -400 FPM
    m_piecewise = new PiecewiseLinearFunction(6);
    m_piecewise->addPoint({ 0.135, 0.4755 });
    m_piecewise->addPoint({ 0.441, 0.3619 });
    m_piecewise->addPoint({ 1.029, 0.2238 });
    m_piecewise->addPoint({ 1.559, 0.1565 });
    m_piecewise->addPoint({ 2.471, 0.0985 });
    m_piecewise->addPoint({ 3.571, 0.0741 });
}
PE::Beeper::~Beeper()
{
    if (m_piecewise != NULL)
        delete m_piecewise;
}
double PE::Beeper::rateFromLiftTone()
{
    double hZ = m_base + m_increment * m_var;
    double rate = hZ / 1000.0;
    if (rate < 0.5) {
        rate = 0.5;
    } else if (rate > 2.0) {
        rate = 2.0;
    } else if (rate == 1.0) {
        rate = 1.0 + DBL_MIN;
    }
    return rate * 1000.0;
}
double PE::Beeper::rateFromSinkTone()
{
    double hZ = m_sinkBase + m_sinkIncrement * m_var;
    double rate = hZ / 500.0;
    if (rate < 0.5) {
        rate = 0.5;
    } else if (rate > 2.0) {
        rate = 2.0;
    } else if (rate == 1.0f) {
        rate = 1.0 + DBL_MAX;
    }
    return rate * 500.0;
}
void PE::Beeper::addValue(double newValue)
{
    m_var = newValue;
    if (newValue > m_climbThreshold) {
        m_climbing = true;
        m_sinking = false;
        m_beeping = true;
        return;
    }
    if (newValue < m_climbThreshold && newValue > m_sinkThreshold) {
        m_beeping = false;
        m_climbing = false;
        m_sinking = false;
        return;
    }
    if (newValue < m_sinkThreshold) {
        m_climbing = false;
        m_sinking = true;
        m_beeping = true;
        return;
    }
}
double PE::Beeper::duration()
{
    return m_piecewise->getValue(m_var) * 1200.0;
}
