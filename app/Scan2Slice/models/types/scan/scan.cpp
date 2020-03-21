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
