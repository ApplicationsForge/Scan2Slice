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

void LinearScanInteractor::execute(double distanceFromLaser, double step, double generalRotationAngle)
{
    Router &router = Router::getInstance();
    Scan s = LinearScanInteractor::joinScans(router.getRepository().scans());
    QList<Scan> scansLinesAlongX = LinearScanInteractor::snakeSplit(s);
    router.getRepository().setScans(LinearScanInteractor::executeSafe(scansLinesAlongX, distanceFromLaser, step, generalRotationAngle));
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
