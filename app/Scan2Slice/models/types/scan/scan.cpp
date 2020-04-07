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

double Scan::medianY(const QList<Point3D> points)
{
    double value = 0.0;
    for(auto point : points)
    {
        value += point.y();
    }

    value = value / points.length();
    return value;
}

QList<Point3D> Scan::removeDuplicatesAndSort(QList<Point3D> points, double precision)
{
    QList<Point3D> result = {};
    std::sort(points.begin(), points.end(), Point3D::cmpX);
    for(int i = 1; i < points.length(); i++)
    {
        if(fabs(points[i-1].x() - points[i].x()) > precision)
        {
            result.append(points[i]);
        }
    }
    return result;
}

void Scan::moveToZero(Scan &s, double distanceToZero, bool useMedianX)
{
    QList<Point3D> points = s.points();
    int pointsCount = points.length();
    double medianX = Scan::medianX(points);
    for(int i = 0; i < pointsCount; i++)
    {
        points[i].setZ(points[i].z() + distanceToZero);
        points[i].setY(0.0);
        if(useMedianX) points[i].setX(medianX);
    }
    s.setPoints(points);
}

void Scan::rotatePoint(Point3D &point, double i)
{
    // перевод градусов в радианы
    double angle = i * M_PI / 180;

    double cosAngle = cos(angle);
    double sinAngle = sin(angle);

    double y = point.y();
    double z = point.z();

    double y_ = 0.0;
    double z_ = 0.0;

    y_ = y * cosAngle - z * sinAngle;
    z_ = y * sinAngle + z * cosAngle;

    point.setY(y_);
    point.setZ(z_);
}
