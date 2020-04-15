#include "linear_scan_interactor.h"

LinearScanInteractor::LinearScanInteractor()
{

}

void LinearScanInteractor::execute(double distanceFromLaser, double step, double toleranceY, double generalRotationAngle)
{
    Router &router = Router::getInstance();
    Scan s = Scan::joinScans(router.getRepository().scans());
    QList<Scan> scansLinesAlongX = Scan::simpleAlongXSplit(s, toleranceY);
    router.getRepository().setScans(LinearScanInteractor::transform(scansLinesAlongX, distanceFromLaser, step, generalRotationAngle));
}

void LinearScanInteractor::snakeExecute(double distanceFromLaser, double step, double generalRotationAngle)
{
    Router &router = Router::getInstance();
    Scan s = Scan::joinScans(router.getRepository().scans());
    QList<Scan> scansLinesAlongX = Scan::snakeAlongXSplit(s);
    router.getRepository().setScans(LinearScanInteractor::transform(scansLinesAlongX, distanceFromLaser, step, generalRotationAngle));
}

QList<Scan> LinearScanInteractor::transform(const QList<Scan> &scans, double distanceFromLaser, double step, double generalRotationAngle)
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
