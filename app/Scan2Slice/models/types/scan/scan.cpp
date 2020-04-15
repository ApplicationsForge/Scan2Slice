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

double Scan::medianValue(const QList<Point3D> points, AXIS_NAME axis)
{
    double value = 0.0;
    for(auto point : points)
    {
        switch (axis)
        {
        case AXIS_NAME::X:
            value += point.x();
            break;
        case AXIS_NAME::Y:
            value += point.y();
            break;
        case AXIS_NAME::Z:
            value += point.z();
            break;
        }
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

QList<Point3D> Scan::medianFilter(const QList<Point3D> &points, double maxOffset, AXIS_NAME axis)
{
    QList<Point3D> result = {points[0]};

    //double medianValue = Scan::medianValue(points, axis);

    for(int i = 1; i < points.length(); i++)
    {
        double currentValue = 0.0;
        double previousValue = 0.0;

        switch (axis)
        {
        case AXIS_NAME::X:
            currentValue = points[i].x();
            previousValue = points[i-1].x();
            break;
        case AXIS_NAME::Y:
            currentValue = points[i].y();
            previousValue = points[i-1].y();
            break;
        case AXIS_NAME::Z:
            currentValue = points[i].z();
            previousValue = points[i-1].z();
            break;
        }

        if(fabs(currentValue - previousValue) <= maxOffset)
        {
            result.append(points[i]);
        }
    }

    qDebug() << points.length() << result.length();
    return result;
}

void Scan::moveToZero(Scan &s, double distanceToZero, bool useMedianX)
{
    QList<Point3D> points = s.points();
    int pointsCount = points.length();
    double medianX = Scan::medianValue(points, AXIS_NAME::X);
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

Scan Scan::joinScans(const QList<Scan> &scans)
{
    Scan s;
    for(auto scan : scans)
    {
        s.append(scan.points());
    }
    return s;
}

QList<Scan> Scan::snakeAlongXSplit(const Scan &s)
{
    QList<Point3D> points = s.points();
    if(points.length() <= 1) return {};

    QList<Scan> result = {};
    Scan tmp({points[0]});
    bool currentDirection = (points[1].x() - points[0].x() > 0);
    for(int i = 1; i < points.length(); i++)
    {
        if((points[i].x() - points[i-1].x() > 0) != currentDirection)
        {
            result.append(tmp);
            tmp = Scan();
            currentDirection = !currentDirection;
        }
        tmp.append(points[i]);
    }

    return result;
}

QList<Scan> Scan::simpleAlongXSplit(const Scan &s, double precision)
{
    QList<Point3D> points = s.points();
    if(points.length() <= 0) return {};

    QList<Scan> result = {};
    Scan tmp;
    tmp.append(points[0]);
    for(int i = 1; i < points.length(); i++)
    {
        if(fabs(points[i].y() - points[i-1].y()) > precision)
        {
            result.append(tmp);
            tmp = Scan();
        }
        tmp.append(points[i]);
    }

    return result;
}
