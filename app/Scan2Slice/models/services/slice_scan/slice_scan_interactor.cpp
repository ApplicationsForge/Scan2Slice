#include "slice_scan_interactor.h"

SliceScanInteractor::SliceScanInteractor()
{

}

void SliceScanInteractor::execute(double distanceFromLaser, double step, double toleranceX, double generalRotationAngle, bool useRotationFix)
{
    Router &router = Router::getInstance();
    QList<Scan> scans = SplitToScansInteractor::execute(router.getRepository().points(), toleranceX);

    int i = 0;
    for(auto& scan : scans)
    {
        ScanToSliceInteractor::execute(scan,
                                       distanceFromLaser,
                                       step,
                                       useRotationFix ? generalRotationAngle - step * i * 2 : generalRotationAngle,
                                       true);
        i++;
    }
    router.getRepository().setScans(scans);
}
