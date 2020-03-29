#include "spiral_scan_interactor.h"

SpiralScanInteractor::SpiralScanInteractor()
{

}

void SpiralScanInteractor::execute(double distanceFromLaser, double step, double generalRotationAngle, double correctionAngle)
{
    Router &router = Router::getInstance();
    Scan s = SpiralScanInteractor::joinScans(router.getRepository().scans());
    ScanToSliceInteractor::execute(s, distanceFromLaser, step, generalRotationAngle, false, true, correctionAngle);
    router.getRepository().setScans({s});
}

Scan SpiralScanInteractor::joinScans(const QList<Scan> &scans)
{
    Scan s;
    for(auto scan : scans)
    {
        s.append(scan.points());
    }
    return s;
}
