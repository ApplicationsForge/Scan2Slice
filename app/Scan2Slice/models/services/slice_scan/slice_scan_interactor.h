#ifndef SLICESCANINTERACTOR_H
#define SLICESCANINTERACTOR_H

#include "models/router.h"
#include "models/services/split_to_scans/split_to_scans_interactor.h"
#include "models/services/scan_to_slice/scan_to_slice_interactor.h"

class SliceScanInteractor
{
public:
    SliceScanInteractor();

    /**
     * @brief Запускает сценарий
     * @param distanceFromLaser - расстояние от лазера до оси вращения
     * @param step - дискретность задания точек в градусах
     * @param toleranceX - точность, в пределах которой точки считаются одним срезом
     * @param generalRotationAngle - угол на который нужно повернуть все точки
     * @param useRotationFix - нужно ли использовать автокоррекцию вращения
     */
    static void execute(double distanceFromLaser, int step, double toleranceX, int generalRotationAngle = 0, bool useRotationFix = false);
};

#endif // SLICESCANINTERACTOR_H
