#include "scan_to_slice_interactor.h"

ScanToSliceInteractor::ScanToSliceInteractor()
{

}

void ScanToSliceInteractor::execute(Scan &s, double distanceToZero, int step, int sliceRotationAngle, bool useMedianX)
{
    ScanToSliceInteractor::moveToZero(s, distanceToZero, useMedianX);
    QList<Point3D> points = s.points();
    for(int i = 0; i < points.length(); i++)
    {
        int angle = (i + sliceRotationAngle + (step - 1) * i) % 360;
        rotate(points[i], angle);
    }
    s.setPoints(points);
}

void ScanToSliceInteractor::moveToZero(Scan &s, double distanceToZero, bool useMedianX)
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

void ScanToSliceInteractor::rotate(Point3D &point, int i)
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
