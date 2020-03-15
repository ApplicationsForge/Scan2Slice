#include "point_3d.h"

Point3D::Point3D() :
    m_x(0.0),
    m_y(0.0),
    m_z(0.0)
{
}

Point3D::Point3D(double x, double y, double z) :
    m_x(x),
    m_y(y),
    m_z(z)
{
}

double Point3D::x() const
{
    return m_x;
}

void Point3D::setX(double x)
{
    m_x = x;
}

double Point3D::y() const
{
    return m_y;
}

void Point3D::setY(double y)
{
    m_y = y;
}

double Point3D::z() const
{
    return m_z;
}

void Point3D::setZ(double z)
{
    m_z = z;
}

QString Point3D::toGCode()
{
    return "G1 X" + QString::number(m_x) + " Y" + QString::number(m_y) + " Z" + QString::number(m_z);
}

bool Point3D::cmpX(Point3D p1, Point3D p2)
{
    return (p1.x() < p2.x());
}

double Point3D::xoyDistance(const Point3D &p1, const Point3D &p2)
{
    return sqrt(pow((p1.x() - p2.x()), 2) + pow((p1.y() - p2.y()), 2));
}
