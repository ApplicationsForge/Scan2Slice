#ifndef READPOINTSFROMFILEINTERACTOR_H
#define READPOINTSFROMFILEINTERACTOR_H

#include <QList>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include "models/types/point_3d/point_3d.h"

#include "models/router.h"

class ReadPointsFromFileInteractor
{
public:
    ReadPointsFromFileInteractor();

    static QList<Point3D> execute(QString fileName = "");
};

#endif // READPOINTSFROMFILEINTERACTOR_H
