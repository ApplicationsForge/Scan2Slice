#include "scan_to_slice_interactor.h"

ScanToSliceInteractor::ScanToSliceInteractor()
{

}

QList<Point3D> ScanToSliceInteractor::execute(QList<Point3D> points)
{
    double d = 80.3;

    for(auto& point : points)
    {
        point.setZ(point.z() + d);
        point.setY(0.0);
    }

    for(int i = 0; i < points.length(); i++)
    {
        // перевод градусов в радианы
        //double angle = i * M_PI / 180;
        double angle = i * 0.0175;

        double cosAngle = cos(angle);
        double sinAngle = sin(angle);

        double y = points[i].y();
        double z = points[i].z();

        y = y * cosAngle - z * sinAngle;
        z = y * sinAngle + z * cosAngle;

        /*y = y * cosAngle + z * sinAngle;
        z = -1 * (y * sinAngle) + z * cosAngle;*/

        points[i].setY(y);
        points[i].setZ(z);
    }

    /*for(auto& point : points)
    {
        point.setZ(point.z() - d);
    }*/

    return points;
}
