#ifndef SCAN_H
#define SCAN_H

#include <QList>

#include "models/types/point_3d/point_3d.h"

class Scan
{
public:
    Scan(QList<Point3D> points = {});

    QList<Point3D> points() const;
    void setPoints(const QList<Point3D> &points);

    void append(const Point3D &point);
    void append(const QList<Point3D> &points);

    static double medianX(const QList<Point3D> points);
    static double medianY(const QList<Point3D> points);

    static void moveToZero(Scan &s, double distanceToZero, bool useMedianX);
    static void rotatePoint(Point3D &point, double i);

private:
    QList<Point3D> m_points;
};

#endif // SCAN_H
