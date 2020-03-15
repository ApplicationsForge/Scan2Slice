#include "scan_to_slice_interactor.h"

ScanToSliceInteractor::ScanToSliceInteractor()
{

}

QList<Point3D> ScanToSliceInteractor::execute(QList<Point3D> points, double distanceToZero, bool inverted)
{
    points = ScanToSliceInteractor::moveToZero(points, distanceToZero);
    return points;
    for(int i = 0; i < points.length(); i++)
    {
        // перевод градусов в радианы
        //double angle = i * M_PI / 180;
        double angle = points[i].y() * 0.0175;

        double cosAngle = cos(angle);
        double sinAngle = sin(angle);

        double y = 0.0;//points[i].y();
        double z = points[i].z();

        if(inverted)
        {
            y = y * cosAngle + z * sinAngle;
            z = -1 * (y * sinAngle) + z * cosAngle;
        }
        else
        {
            y = y * cosAngle - z * sinAngle;
            z = y * sinAngle + z * cosAngle;
        }

        points[i].setY(y);
        points[i].setZ(z);
    }

    return points;
}

QList<Point3D> ScanToSliceInteractor::moveToZero(QList<Point3D> points, double distanceToZero)
{
    int pointsCount = points.length();
    double yCoord = 0.0;
    for(int i = 0; i < std::min(90, pointsCount); i++)
    {
        // x = distanceToZero - fabs(points[i].z())

        points[i].setZ(distanceToZero - fabs(points[i].z()));
        points[i].setY(yCoord);
        yCoord++;
    }

    if(pointsCount > 90)
    {
        for(int i = 90; i < std::min(270, pointsCount); i++)
        {
            points[i].setZ(-1*(points[i].z() + distanceToZero));
            points[i].setY(yCoord);
            yCoord--;
        }
    }

    if(pointsCount > 270)
    {
        for(int i = 270; i < std::min(360, pointsCount); i++)
        {
            points[i].setZ(points[i].z() + distanceToZero);
            points[i].setY(yCoord);
            yCoord++;
        }
    }
    return points;
}
