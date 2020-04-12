#ifndef LINEARINTERPOLATEDPOLYNOMIAL_H
#define LINEARINTERPOLATEDPOLYNOMIAL_H

#include <QList>

#include "models/types/linear_interpolation/linear_equation.h"
#include "models/types/point_3d/point_3d.h"

class LinearInterpolatedPolynomial
{
public:
    LinearInterpolatedPolynomial(const QList<Point3D> &points);

    double solve(double _x);

private:
    QList<LinearEquation> m_equations;
};

#endif // LINEARINTERPOLATEDPOLYNOMIAL_H
