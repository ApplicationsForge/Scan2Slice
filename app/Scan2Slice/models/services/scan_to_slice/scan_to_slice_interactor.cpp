#include "scan_to_slice_interactor.h"

ScanToSliceInteractor::ScanToSliceInteractor()
{

}

QList<Point3D> ScanToSliceInteractor::execute(QList<Point3D> points, double distanceToZero, bool inverted)
{
    points = ScanToSliceInteractor::moveToZero(points, distanceToZero);

    for(int i = 0; i < points.length(); i++)
    {
        rotate(points[i], i, inverted);
    }

    return points;
}

QList<Point3D> ScanToSliceInteractor::moveToZero(QList<Point3D> points, double distanceToZero)
{
    int pointsCount = points.length();
    for(int i = 0; i < pointsCount; i++)
    {
        points[i].setZ(points[i].z() + distanceToZero);
        points[i].setY(0.0);
        points[i].setX(0.0);
    }
    return points;
}

void ScanToSliceInteractor::rotate(Point3D &point, int i, bool inverted)
{
    // перевод градусов в радианы
    double angle = i * M_PI / 180;
    //double angle = i * 0.0175;

    double cosAngle = cos(angle);
    double sinAngle = sin(angle);

    double y = point.y();
    double z = point.z();

    double y_ = 0.0;
    double z_ = 0.0;

    if(inverted)
    {
        y_ = y * cosAngle + z * sinAngle;
        z_ = -1 * (y * sinAngle) + z * cosAngle;
    }
    else
    {
        y_ = y * cosAngle - z * sinAngle;
        z_ = y * sinAngle + z * cosAngle;
    }

    point.setY(y_);
    point.setZ(z_);
}
