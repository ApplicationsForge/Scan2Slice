#ifndef SCANTOSLICEINTERACTOR_H
#define SCANTOSLICEINTERACTOR_H

#include <QList>
#include <QDebug>
#include "models/types/point_3d/point_3d.h"
#include "models/types/scan/scan.h"
#include "math.h"

class ScanToSliceInteractor
{
public:
    ScanToSliceInteractor();

    static void execute(Scan &s,
                        double distanceToZero,
                        double step = 1,
                        double generalRotationAngle = 0,
                        bool useMedianX = false,
                        bool useMod360 = true);

private:
    static void moveToZero(Scan &s, double distanceToZero, bool useMedianX);
    static void rotate(Point3D &point, double i);
};

#endif // SCANTOSLICEINTERACTOR_H
