#ifndef SAVEPOINTSTOFILEINTERACTOR_H
#define SAVEPOINTSTOFILEINTERACTOR_H

#include <QList>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include "models/types/point_3d/point_3d.h"

class SavePointsToFileInteractor
{
public:
    SavePointsToFileInteractor();

    static void execute(const QList<Point3D> points, QString fileName);
};

#endif // SAVEPOINTSTOFILEINTERACTOR_H
