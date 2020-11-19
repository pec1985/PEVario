#ifndef Altimeter_H_
#define Altimeter_H_

namespace PE
{
class KalmanFilter;
class Altimeter {
public:
    Altimeter();
    ~Altimeter();
    void setSealevelPressure(double pressure);
    void addPressure(double pressure, double time);
    void setAltitude(double alt);
    double altitude();
    double varioValue();

private:
    double m_seaLevelPressure;
    double m_rawPressure;
    double m_rawAltitude;
    double m_positionNoise;
    double m_altDamp;
    double m_dampedAltitude;

    KalmanFilter* m_kalmanFilter;
    bool m_dampedAltStarted;
};
} // namespace PE
#endif
