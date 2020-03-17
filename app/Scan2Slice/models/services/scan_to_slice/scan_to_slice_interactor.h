#ifndef SCANTOSLICEINTERACTOR_H
#define SCANTOSLICEINTERACTOR_H

#include <QList>
#include <QDebug>
#include "models/types/point_3d/point_3d.h"
#include "math.h"

class ScanToSliceInteractor
{
public:
    ScanToSliceInteractor();

    static QList<Point3D> execute(QList<Point3D> points, double distanceToZero, bool inverted);

private:
    static QList<Point3D> moveToZero(QList<Point3D> points, double distanceToZero);
    static void rotate(Point3D &point, int i, bool inverted = false);
};

#endif // SCANTOSLICEINTERACTOR_H
