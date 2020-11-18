#ifndef Beeper_H_
#define Beeper_H_

namespace PE
{
class PiecewiseLinearFunction;
class Beeper {
public:
    Beeper();
    ~Beeper();
    double rateFromLiftTone();
    double rateFromSinkTone();
    void addValue(double newValue);
    double duration();
    inline bool sinking()
    {
        return m_sinking;
    }
    inline bool climbing()
    {
        return m_climbing;
    }
    inline bool beeping()
    {
        return m_beeping;
    }
    inline void setClimbThreshold(double value)
    {
        m_climbThreshold = value;
    }
    inline void setSinkThreshold(double value)
    {
        m_sinkThreshold = value;
    }
    inline double climbThreshold()
    {
        return m_climbThreshold;
    }
    inline double sinkThreshold()
    {
        return m_sinkThreshold;
    }

private:
    PiecewiseLinearFunction* m_piecewise;
    double m_climbThreshold;
    double m_sinkThreshold;
    double m_var;
    bool m_climbing;
    bool m_sinking;
    bool m_beeping;
    double m_increment;
    double m_base;
    double m_sinkBase;
    double m_sinkIncrement;
};
} // namespace PE

#endif