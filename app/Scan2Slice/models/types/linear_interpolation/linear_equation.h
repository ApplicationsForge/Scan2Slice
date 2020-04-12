#ifndef LINEAREQUATION_H
#define LINEAREQUATION_H

#include <QDebug>

#include "models/types/point_3d/point_3d.h"

class LinearEquation
{
public:
    LinearEquation(Point3D p1, Point3D p2);

    double solve(double _x);

    double lowerBound() const;

    double upperBound() const;

private:
    // x1 = x[i - 1]
    // x2 = x[i]
    void train(double x1, double y1, double x2, double y2);
    double m_b;
    double m_k;
    double m_lowerBound;
    double m_upperBound;
};

#endif // LINEAREQUATION_H
