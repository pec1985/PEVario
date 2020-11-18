#include "Vario.hpp"
#include "Altimeter.hpp"
#include "Beeper.hpp"

#include <iostream>

PE::Vario::Vario()
{
}

PE::Vario::~Vario()
{
    if (m_altimeter != NULL)
        delete m_altimeter;
    if (m_beeper != NULL)
        delete m_beeper;
}
void PE::Vario::begin(double now)
{
    m_time = now;
    m_altimeter = new PE::Altimeter();
    m_beeper = new PE::Beeper();
}

void PE::Vario::update(double pressure, double now)
{
    auto time = now - m_time;
    m_time = now;
    m_altimeter->addPressure(pressure, (time) / 1000);
    m_climbRate = m_altimeter->varioValue();
    m_altitude = m_altimeter->altitude();
    m_beeper->addValue(m_climbRate);
    updateBeep();
}
void PE::Vario::resetTime(double now)
{
    m_time = now;
}

void PE::Vario::updateBeep()
{
    if (m_beeper->beeping()) {
        auto climbing = m_beeper->climbing();
        auto sinking = m_beeper->sinking();
        if (climbing || sinking) {
            auto duration = m_beeper->duration();
            if (m_time >= m_stopBeepingAt && m_shouldStopBeeping) {
                m_shouldStopBeeping = false;
                m_shouldStartBeeping = true;
                m_startedBeeping = false;
                m_canStartBeepingAt = m_time + duration;
                if (climbing) {
                    beep(false, 0, 0);
                }
                return;
            } else if (m_time >= m_canStartBeepingAt && m_shouldStartBeeping) {
                m_shouldStartBeeping = false;
                m_startedBeeping = true;
                m_stopBeepingAt = m_time + duration;
                m_shouldStopBeeping = true;
            }

            if (m_startedBeeping) {
                auto freq = climbing ? m_beeper->rateFromLiftTone() : m_beeper->rateFromSinkTone();
                beep(climbing, freq, duration);
            }
        } else {
            beep(false, 0, 0);
        }
    } else {
        beep(false, 0, 0);
    }
}

void PE::Vario::setClimbThreshold(double value)
{
    m_beeper->setClimbThreshold(value);
}
void PE::Vario::setSinkThreshold(double value)
{
    m_beeper->setSinkThreshold(value);
}
double PE::Vario::climbThreshold()
{
    return m_beeper->climbThreshold();
}
double PE::Vario::sinkThreshold()
{
    return m_beeper->sinkThreshold();
}

void PE::Vario::beep(bool climbing, double freq, double duration)
{
    if (freq == 0) {
        m_callback(0, 0, false);
    } else {
        auto hasSound = climbing ? m_beepsOnLift : m_beepsOnSink;
        if (hasSound) {
            m_callback(freq, duration, true);
        }
    }
}
