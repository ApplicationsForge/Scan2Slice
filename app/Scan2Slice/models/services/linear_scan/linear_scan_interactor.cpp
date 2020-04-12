#include "linear_scan_interactor.h"

LinearScanInteractor::LinearScanInteractor()
{

}

void LinearScanInteractor::execute(double distanceFromLaser, double step, double toleranceY, double generalRotationAngle)
{
    Router &router = Router::getInstance();
    Scan s = LinearScanInteractor::joinScans(router.getRepository().scans());
    QList<Scan> scansLinesAlongX = LinearScanInteractor::splitByAxisX(s, toleranceY);
    router.getRepository().setScans(LinearScanInteractor::executeSafe(scansLinesAlongX, distanceFromLaser, step, generalRotationAngle));
}

void LinearScanInteractor::snakeExecute(double distanceFromLaser, double step, double generalRotationAngle)
{
    Router &router = Router::getInstance();
    Scan s = LinearScanInteractor::joinScans(router.getRepository().scans());
    QList<Scan> scansLinesAlongX = LinearScanInteractor::snakeSplit(s);
    router.getRepository().setScans(LinearScanInteractor::executeSafe(scansLinesAlongX, distanceFromLaser, step, generalRotationAngle));
}

void LinearScanInteractor::sliceExecute(double distanceFromLaser, double step, double generalRotationAngle, double lowerBound, double upperBound, double sliceStep, double medianFilterOffset)
{
    Router &router = Router::getInstance();
    Scan s = LinearScanInteractor::joinScans(router.getRepository().scans());
    QList<Scan> scansLinesAlongX = LinearScanInteractor::snakeSplit(s);
    scansLinesAlongX = LinearScanInteractor::executeSafe(scansLinesAlongX, distanceFromLaser, step, generalRotationAngle);
    QList<Scan> slices = LinearScanInteractor::getSlices(scansLinesAlongX, lowerBound, upperBound, sliceStep, medianFilterOffset);
    router.getRepository().setScans(slices);
}

QList<Scan> LinearScanInteractor::executeSafe(const QList<Scan> &scans, double distanceFromLaser, double step, double generalRotationAngle)
{
    QList<Scan> result = {};
    double currentRotationAngle = generalRotationAngle;
    for(auto scan : scans)
    {
        Scan::moveToZero(scan, distanceFromLaser, false);
        QList<Point3D> scanPoints = scan.points();
        for(auto& point : scanPoints)
        {
            Scan::rotatePoint(point, currentRotationAngle);
        }
        scan.setPoints(scanPoints);
        currentRotationAngle += step;

        result.append(scan);
        if(currentRotationAngle > 360 + generalRotationAngle) break;
    }
    return result;
}

Scan LinearScanInteractor::joinScans(const QList<Scan> &scans)
{
    Scan s;
    for(auto scan : scans)
    {
        s.append(scan.points());
    }
    return s;
}

QList<Scan> LinearScanInteractor::splitByAxisX(const Scan &s, double precision)
{
    QList<Point3D> points = s.points();
    if(points.length() <= 0) return {};

    QList<Scan> result = {};
    Scan tmp;
    tmp.append(points[0]);
    for(int i = 1; i < points.length(); i++)
    {
        if(fabs(points[i].y() - points[i-1].y()) > precision)
        {
            result.append(tmp);
            tmp = Scan();
        }
        tmp.append(points[i]);
    }

    return result;
}

QList<Scan> LinearScanInteractor::snakeSplit(const Scan &s)
{
    QList<Point3D> points = s.points();
    if(points.length() <= 1) return {};

    QList<Scan> result = {};
    Scan tmp({points[0]});
    bool currentDirection = (points[1].x() - points[0].x() > 0);
    for(int i = 1; i < points.length(); i++)
    {
        if((points[i].x() - points[i-1].x() > 0) != currentDirection)
        {
            result.append(tmp);
            tmp = Scan();
            currentDirection = !currentDirection;
        }
        tmp.append(points[i]);
    }

    return result;
}

QList<Scan> LinearScanInteractor::getSlicesAlt(const QList<Scan> &scans, double lowerBound, double upperBound, double sliceStep, double medianFilterOffset)
{
    QList< QPair<double, tk::spline> > splines = {};
    for(auto scan : scans)
    {
        QList<Point3D> scanPoints = scan.points();
        scanPoints = Scan::removeDuplicatesAndSort(scanPoints, 0.001);

        if(medianFilterOffset > 0) scanPoints = Scan::medianFilter(scanPoints, medianFilterOffset, AXIS_NAME::Z);

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
        s.set_boundary(tk::spline::second_deriv, 0.0,
                           tk::spline::first_deriv, -2.0, false);
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

QList<Scan> LinearScanInteractor::getSlices(const QList<Scan> &scans, double lowerBound, double upperBound, double sliceStep, double medianFilterOffset)
{
    QList< QPair<double, LinearInterpolatedPolynomial> > lines = {};
    //for(auto scan : scans)
    for(int i = 0; i < scans.length() / 2; i++)
    {
        QList<Point3D> scanPoints = scans[i].points();
        scanPoints = Scan::removeDuplicatesAndSort(scanPoints, 0.001);

        if(medianFilterOffset > 0) scanPoints = Scan::medianFilter(scanPoints, medianFilterOffset, AXIS_NAME::Z);

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
