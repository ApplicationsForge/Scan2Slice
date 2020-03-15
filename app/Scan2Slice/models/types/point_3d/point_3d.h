#ifndef POINT_3D_H
#define POINT_3D_H

#include "math.h"

class Point3D
{
public:
    explicit Point3D();
    explicit Point3D(double x, double y, double z);


    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    double z() const;
    void setZ(double z);

    static bool cmpX(Point3D p1, Point3D p2);

    static double xoyDistance(const Point3D &p1, const Point3D &p2);

private:
    double m_x;
    double m_y;
    double m_z;
};

#endif // POINT_3D_H
