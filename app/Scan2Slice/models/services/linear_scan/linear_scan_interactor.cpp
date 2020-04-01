#include "linear_scan_interactor.h"

LinearScanInteractor::LinearScanInteractor()
{

}

void LinearScanInteractor::execute(double distanceFromLaser, double step, double toleranceY, double generalRotationAngle)
{
    Router &router = Router::getInstance();
    Scan s = LinearScanInteractor::joinScans(router.getRepository().scans());
    QList<Scan> scansLinesAlongX = LinearScanInteractor::splitByAxisX(s, toleranceY);

    double currentRotationAngle = generalRotationAngle;
    for(auto& scan : scansLinesAlongX)
    {
        Scan::moveToZero(scan, distanceFromLaser, false);
        qDebug() << "rotate" << scan.points().length() << "points" << currentRotationAngle;

        QList<Point3D> scanPoints = scan.points();
        for(auto& point : scanPoints)
        {
            Scan::rotatePoint(point, currentRotationAngle);
        }
        scan.setPoints(scanPoints);
        currentRotationAngle += step;
    }
    router.getRepository().setScans(scansLinesAlongX);}

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

    qDebug() << "total" << result.length();

    return result;
}
