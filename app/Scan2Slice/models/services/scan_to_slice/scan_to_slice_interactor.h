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

    static void execute(Scan &s, double distanceToZero, int step = 1, int sliceRotationAngle = 0);

private:
    static void moveToZero(Scan &s, double distanceToZero);
    static void rotate(Point3D &point, int i);
};

#endif // SCANTOSLICEINTERACTOR_H
