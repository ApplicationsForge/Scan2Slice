#include "linear_interpolated_polynomial.h"

LinearInterpolatedPolynomial::LinearInterpolatedPolynomial(const QList<Point3D> &points)
{
    for(int i = 1; i < points.length(); i++)
    {
        m_equations.append(LinearEquation(points[i-1], points[i]));
    }

}

double LinearInterpolatedPolynomial::solve(double _x)
{
    double result = 0.0;

    for(auto equation : m_equations)
    {
        if(equation.lowerBound() < _x && equation.upperBound() > _x)
        {
            result = equation.solve(_x);
            break;
        }
    }
    return result;
}
