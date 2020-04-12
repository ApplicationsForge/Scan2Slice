#ifndef SCAN_H
#define SCAN_H

#include <QList>
#include <QDebug>

#include "models/types/point_3d/point_3d.h"

enum AXIS_NAME {
    X, Y, Z
};

class Scan
{
public:
    Scan(QList<Point3D> points = {});

    QList<Point3D> points() const;
    void setPoints(const QList<Point3D> &points);

    void append(const Point3D &point);
    void append(const QList<Point3D> &points);

    static double medianValue(const QList<Point3D> points, AXIS_NAME axis);
    static QList<Point3D> removeDuplicatesAndSort(QList<Point3D> points, double precision);
    static QList<Point3D> medianFilter(const QList<Point3D> &points, double maxOffset, AXIS_NAME axis);

    static void moveToZero(Scan &s, double distanceToZero, bool useMedianX);
    static void rotatePoint(Point3D &point, double i);

private:
    QList<Point3D> m_points;
};

#endif // SCAN_H
