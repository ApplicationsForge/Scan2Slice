#include "linear_equation.h"

LinearEquation::LinearEquation(Point3D p1, Point3D p2):
    m_lowerBound(std::min(p1.x(), p2.x())),
    m_upperBound(std::max(p1.x(), p2.x()))
{
    this->train(p1.x(), p1.z(), p2.x(), p2.z());
}

void LinearEquation::train(double x1, double y1, double x2, double y2)
{
    m_k = (y2 - y1) / (x2 - x1);
    m_b = y1 - m_k * x1;
    qDebug() << "train" << x1 << y1 << x2 << y2 << m_k << m_b;
}

double LinearEquation::upperBound() const
{
    return m_upperBound;
}

double LinearEquation::lowerBound() const
{
    return m_lowerBound;
}

double LinearEquation::solve(double _x)
{
    return _x * m_k + m_b;
}
