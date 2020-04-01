#ifndef LINEARSCANINTERACTOR_H
#define LINEARSCANINTERACTOR_H

#include "models/router.h"
#include "models/services/scan_to_slice/scan_to_slice_interactor.h"

class LinearScanInteractor
{
public:
    LinearScanInteractor();

    /**
     * @brief Запускает сценарий
     * @param distanceFromLaser - расстояние от лазера до оси вращения
     * @param step - дискретность задания точек в градусах
     * @param generalRotationAngle - угол на который нужно повернуть все точки
     */
    static void execute(double distanceFromLaser, double step, double generalRotationAngle = 0);
};

#endif // LINEARSCANINTERACTOR_H
