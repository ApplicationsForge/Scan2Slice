#include "scan_to_slice_interactor.h"

ScanToSliceInteractor::ScanToSliceInteractor()
{

}

void ScanToSliceInteractor::execute(Scan &s, double distanceToZero, double step, double generalRotationAngle, bool useMedianX, bool useMod360, double correctionAngle)
{
    Scan::moveToZero(s, distanceToZero, useMedianX);
    QList<Point3D> points = s.points();

    double correctionAngleCurrentValue = 0;
    for(int i = 0; i < points.length(); i++)
    {
        double angle = generalRotationAngle + step * i;
        if(useMod360)
        {
            double mantis = angle - int(angle);
            angle = int(angle) % 360 + mantis;
        }

        //qDebug() << angle << correctionAngleCurrentValue;
        Scan::rotatePoint(points[i], angle + correctionAngleCurrentValue);

        if(int(angle) % 360 == 0)
        {
            correctionAngleCurrentValue += correctionAngle;
        }
    }
    s.setPoints(points);
}
