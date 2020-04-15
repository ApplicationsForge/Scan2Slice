#ifndef SPLITTOSLICESINTERACTOR_H
#define SPLITTOSLICESINTERACTOR_H


#include "models/router.h"
#include "libs/spline/src/spline.h"
#include "models/types/linear_interpolation/linear_interpolated_polynomial.h"


class SplitToSlicesInteractor
{
public:
    SplitToSlicesInteractor();

    static void execute(double lowerBound, double upperBound, double sliceStep);

private:
    static QList<Scan> splitBySplines(const QList<Scan> &scans, double lowerBound, double upperBound, double sliceStep);
    static QList<Scan> splitByPolynimials(const QList<Scan> &scans, double lowerBound, double upperBound, double sliceStep);
};

#endif // SPLITTOSLICESINTERACTOR_H
