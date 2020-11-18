#ifndef PiecewiseLinearFunction_H_
#define PiecewiseLinearFunction_H_

namespace PE
{
struct Point {
    double x;
    double y;
};
class PiecewiseLinearFunction {
public:
    PiecewiseLinearFunction(int capacity);
    ~PiecewiseLinearFunction();
    void addPoint(const Point& point);
    double getValue(double x);

private:
    int m_pointsCount;
    Point* m_points;
    double m_posInfValue;
    double m_negInfValue;
};
} // namespace PE
#endif