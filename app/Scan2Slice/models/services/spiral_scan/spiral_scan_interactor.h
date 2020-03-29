#ifndef SPIRALSCANINTERACTOR_H
#define SPIRALSCANINTERACTOR_H

#include "models/router.h"
#include "models/services/scan_to_slice/scan_to_slice_interactor.h"

class SpiralScanInteractor
{
public:
    SpiralScanInteractor();

    /**
     * @brief Запускает сценарий
     * @param distanceFromLaser - расстояние от лазера до оси вращения
     * @param step - дискретность задания точек в градусах
     * @param generalRotationAngle - угол на который нужно повернуть все точки
     * @param correctionAngle - угол доворота каждого витка спирали
     */
    static void execute(double distanceFromLaser, double step, double generalRotationAngle = 0, double correctionAngle = 0);

private:
    static Scan joinScans(const QList<Scan> &scans);
};

#endif // SPIRALSCANINTERACTOR_H
