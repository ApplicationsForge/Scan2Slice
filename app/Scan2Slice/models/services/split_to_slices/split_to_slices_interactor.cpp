#include "split_to_slices_interactor.h"

SplitToSlicesInteractor::SplitToSlicesInteractor()
{

}

void SplitToSlicesInteractor::execute(double lowerBound, double upperBound, double sliceStep)
{
    Router &router = Router::getInstance();
    Scan s = Scan::joinScans(router.getRepository().scans());
    QList<Scan> scansAlongX = Scan::snakeAlongXSplit(s);
    QList<Scan> slices = SplitToSlicesInteractor::splitBySplines(scansAlongX, lowerBound, upperBound, sliceStep);
    router.getRepository().setScans(slices);
}

QList<Scan> SplitToSlicesInteractor::splitBySplines(const QList<Scan> &scans, double lowerBound, double upperBound, double sliceStep)
{
    QList< QPair<double, tk::spline> > splines = {};
    for(auto scan : scans)
    {
        QList<Point3D> scanPoints = scan.points();
        scanPoints = Scan::removeDuplicatesAndSort(scanPoints, 0.001);

        if(scanPoints.length() <= 3) {
            qDebug() << "too small count of points" << scanPoints.length();
            continue;
        }

        std::vector<double> arguments = {};
        std::vector<double> results = {};
        for(auto point : scanPoints)
        {
            arguments.push_back(point.x());
            results.push_back(point.z());
        }
        double yLevel = Scan::medianValue(scanPoints, AXIS_NAME::Y);

        tk::spline s;
        s.set_points(arguments, results);
        splines.append(QPair<double, tk::spline>(yLevel, s));
    }

    QList<Scan> result = {};
    for(double i = lowerBound; i < upperBound; i += sliceStep)
    {
        QList<Point3D> slicePoints = {};
        for(auto spline : splines)
        {
            double _x = i;
            double _y = spline.first;
            double _z = spline.second(i);
            slicePoints.append(Point3D(_x, _y, _z));
        }
        Scan slice(slicePoints);
        result.append(slice);
    }
    return result;
}

QList<Scan> SplitToSlicesInteractor::splitByPolynimials(const QList<Scan> &scans, double lowerBound, double upperBound, double sliceStep)
{
    QList< QPair<double, LinearInterpolatedPolynomial> > lines = {};
    //for(auto scan : scans)
    for(int i = 0; i < scans.length() / 2; i++)
    {
        QList<Point3D> scanPoints = scans[i].points();
        scanPoints = Scan::removeDuplicatesAndSort(scanPoints, 0.001);

        if(scanPoints.length() <= 3) {
            qDebug() << "too small count of points" << scanPoints.length();
            continue;
        }

        double yLevel = Scan::medianValue(scanPoints, AXIS_NAME::Y);
        LinearInterpolatedPolynomial p(scanPoints);
        lines.append(QPair<double, LinearInterpolatedPolynomial>(yLevel, p));
    }

    QList<Scan> result = {};
    for(double i = lowerBound; i < upperBound; i += sliceStep)
    {
        QList<Point3D> slicePoints = {};
        for(auto line : lines)
        {
            double _x = i;
            double _y = line.first;
            double _z = line.second.solve(i);
            slicePoints.append(Point3D(_x, _y, _z));
        }
        Scan slice(slicePoints);
        result.append(slice);
    }
    return result;
}
