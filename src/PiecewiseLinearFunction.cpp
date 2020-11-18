
#include "PiecewiseLinearFunction.hpp"
#include <stdlib.h>

#define POS_INFINITY 0x7ff0000000000000L
#define NEG_INFINITY 0xfff0000000000000L

PE::PiecewiseLinearFunction::PiecewiseLinearFunction(int capacity)
{
    m_points = (Point*)malloc(sizeof(Point) * capacity);
    m_posInfValue = POS_INFINITY;
    m_negInfValue = NEG_INFINITY;
    m_pointsCount = 0;
}
PE::PiecewiseLinearFunction::~PiecewiseLinearFunction()
{
    free(m_points);
}
void PE::PiecewiseLinearFunction::addPoint(const Point& point)
{
    if (m_pointsCount == 0) {
        m_points[m_pointsCount] = point;
    } else if (point.x > (m_points[m_pointsCount - 1].x)) {
        m_points[m_pointsCount] = point;
    } else {
        for (int i = 0; i < m_pointsCount; i++) {
            if (m_points[i].x > point.x) {
                m_points[i] = point;
                return;
            }
        }
    }
    m_pointsCount++;
}
double PE::PiecewiseLinearFunction::getValue(double x)
{
    if (x == POS_INFINITY) {
        return m_posInfValue;
    } else if (x == NEG_INFINITY) {
        return m_negInfValue;
    } else if (m_pointsCount == 1) {
        return m_points[0].y;
    } else {
        Point point;
        Point lastPoint = m_points[0];
        if (x <= lastPoint.x) {
            return lastPoint.y;
        }
        for (int i = 1; i < m_pointsCount; i++) {
            point = m_points[i];
            if (x <= point.x) {
                double ratio = (x - lastPoint.x) / (point.x - lastPoint.x);
                return lastPoint.y + ratio * (point.y - lastPoint.y);
            }
            lastPoint = point;
        }
        return lastPoint.y;
    }
}
