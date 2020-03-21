#include "scan.h"

Scan::Scan(QList<Point3D> points) :
    m_points(points)
{

}

QList<Point3D> Scan::points() const
{
    return m_points;
}

void Scan::setPoints(const QList<Point3D> &points)
{
    m_points = points;
}

void Scan::append(const Point3D &point)
{
    m_points.append(point);
}

void Scan::append(const QList<Point3D> &points)
{
    m_points.append(points);
}

double Scan::medianX(const QList<Point3D> points)
{
    double value = 0.0;
    for(auto point : points)
    {
        value += point.x();
    }

    value = value / points.length();
    return value;
}
