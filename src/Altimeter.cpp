#include "Altimeter.hpp"
#include "KalmanFilter.hpp"
#include <math.h>

#define STANDARD_SEA_LEVEL_PRESSURE 101325.0

PE::Altimeter::Altimeter()
{
    setSealevelPressure(STANDARD_SEA_LEVEL_PRESSURE);
    m_kalmanFilter = new KalmanFilter(1.0);
    m_positionNoise = 0.2;
    m_altDamp = 0.05;
}
PE::Altimeter::~Altimeter()
{
    delete m_kalmanFilter;
}
void PE::Altimeter::setSealevelPressure(double pressure)
{
    m_rawPressure = pressure;
    m_seaLevelPressure = pressure;
    m_dampedAltStarted = false;
}
void PE::Altimeter::addPressure(double pressure, double time)
{
    m_rawPressure = pressure;
    m_rawAltitude = 44330.0 * (1.0 - pow((m_rawPressure / m_seaLevelPressure), 0.190295));
    if (m_dampedAltStarted) {
        m_dampedAltitude = m_dampedAltitude + m_altDamp * (m_rawAltitude - m_dampedAltitude);
    } else {
        m_dampedAltitude = m_rawAltitude;
        m_dampedAltStarted = true;
    }
    m_kalmanFilter->update(m_dampedAltitude, m_positionNoise, time);
}
void PE::Altimeter::setAltitude(double alt)
{
    m_dampedAltitude = alt;
    m_dampedAltStarted = true;
    m_seaLevelPressure = m_rawPressure / pow(1.0 - (m_dampedAltitude / 44330.0), 5.255);
}
double PE::Altimeter::altitude()
{
    return m_kalmanFilter->getXAbs();
}
double PE::Altimeter::varioValue()
{
    return m_kalmanFilter->getXVel();
}
