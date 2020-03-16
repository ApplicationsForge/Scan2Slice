#include "scan_to_slice_interactor.h"

ScanToSliceInteractor::ScanToSliceInteractor()
{

}

QList<Point3D> ScanToSliceInteractor::execute(QList<Point3D> points, double distanceToZero, bool inverted)
{
    points = ScanToSliceInteractor::moveToZero(points, distanceToZero);

    for(int i = 0; i < points.length(); i++)
    {
        // перевод градусов в радианы
        double angle = i * M_PI / 180;
        //double angle = i * 0.0175;

        double cosAngle = cos(angle);
        double sinAngle = sin(angle);

        double y = points[i].y();
        double z = points[i].z();

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

        qDebug() << i << angle << sinAngle << cosAngle << points[i].y() << points[i].z() << y_ << z_;

        points[i].setY(y_);
        points[i].setZ(z_);

        qDebug() << points[i].x() << points[i].y() << points[i].z();
    }

    return points;
}

QList<Point3D> ScanToSliceInteractor::moveToZero(QList<Point3D> points, double distanceToZero)
{
    int pointsCount = points.length();
    for(int i = 0; i < std::min(90, pointsCount); i++)
    {
        points[i].setZ(points[i].z() + distanceToZero);
        points[i].setY(0.0);
    }

    if(pointsCount > 90)
    {
        for(int i = 90; i < std::min(271, pointsCount); i++)
        {
            points[i].setZ(-1*(points[i].z() + distanceToZero));
            points[i].setY(0.0);
        }
    }

    if(pointsCount > 270)
    {
        for(int i = 270; i < std::min(360, pointsCount); i++)
        {
            points[i].setZ(points[i].z() + distanceToZero);
            points[i].setY(0.0);
        }
    }
    return points;
}
