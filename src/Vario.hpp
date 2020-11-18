
#ifndef Vario_H_
#define Vario_H_

#ifndef NULL
#define NULL 0
#endif

namespace PE {
typedef void (*VarioCallback)(double freq, double duration, bool silent);

class Beeper;
class Altimeter;
class Vario {
public:
    Vario();
    ~Vario();
    void begin(double now);
    void update(double pressure, double now);
    void resetTime(double now);
    Altimeter* altimeter() {
        return m_altimeter;
    }
    double climbRate() const
    {
        return m_climbRate;
    }
    double altitude() const
    {
        return m_altitude - m_altDiff;
    }
    double altitudeMsl() const
    {
        return m_altitude;
    }
    void setBeepsOnSink(bool val)
    {
        m_beepsOnSink = val;
    }
    void setCallback(VarioCallback callback)
    {
        m_callback = callback;
    }
    void setAltitude(double alt)
    {
        m_altDiff = m_altitude - alt;
    }
    void setClimbThreshold(double value);
    void setSinkThreshold(double value);
    double climbThreshold();
    double sinkThreshold();
    const bool beepsOnSink()
    {
        return m_beepsOnSink;
    }

private:
    void updateBeep();
    void beep(bool climbing, double freq, double duration);
    double m_climbRate{ 0 };
    double m_altitude{ 0 };

    double m_time{ -1 };
    double m_altDiff{ 0 };

    bool m_beepsOnLift{ true };
    bool m_beepsOnSink{ true };
    bool m_startedBeeping{ false };
    bool m_shouldStartBeeping{ true };
    bool m_shouldStopBeeping{ false };
    double m_canStartBeepingAt{ 0 };
    double m_stopBeepingAt{ 0 };

    Beeper* m_beeper{ NULL };
    Altimeter* m_altimeter{ NULL };
    VarioCallback m_callback;
};
} // namespace PE
#endif