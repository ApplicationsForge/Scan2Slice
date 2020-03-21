#ifndef SPLITTOSCANSINTERACTOR_H
#define SPLITTOSCANSINTERACTOR_H

#include <QList>
#include <QString>

#include "models/types/point_3d/point_3d.h"
#include "models/types/scan/scan.h"

class SplitToScansInteractor
{
public:
    SplitToScansInteractor();

    static QList<Scan> execute(QList<Point3D> points);
};

#endif // SPLITTOSCANSINTERACTOR_H
