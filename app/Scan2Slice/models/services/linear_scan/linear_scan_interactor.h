#ifndef LINEARSCANINTERACTOR_H
#define LINEARSCANINTERACTOR_H

#include <QDebug>

#include "models/router.h"
#include "libs/spline/src/spline.h"

class LinearScanInteractor
{
public:
    LinearScanInteractor();

    /**
     * @brief Запускает сценарий
     * @param distanceFromLaser - расстояние от лазера до оси вращения
     * @param step - дискретность угла поворота в градусах
     * @param toleranceY - допустимое отклонение точек одной линии по оси Y
     * @param generalRotationAngle - угол на который нужно повернуть все точки
     */
    static void execute(double distanceFromLaser, double step, double toleranceY, double generalRotationAngle);

    /**
     * @brief Запускает сценарий (сканирвоание змейкой)
     * @param distanceFromLaser - расстояние от лазера до оси вращения
     * @param step - дискретность угла поворота в градусах
     * @param generalRotationAngle - угол на который нужно повернуть все точки
     */
    static void execute(double distanceFromLaser, double step, double generalRotationAngle);

    /**
     * @brief Запускает сценарий без модификации данных
     * @param scans - исходные сканы
     * @param distanceFromLaser - расстояние от лазера до оси вращения
     * @param step - дискретность угла поворота в градусах
     * @param generalRotationAngle - угол на который нужно повернуть все точки
     * @return преобразованные сканы
     */
    static QList<Scan> executeSafe(const QList<Scan> &scans, double distanceFromLaser, double step, double generalRotationAngle);
private:

    static Scan joinScans(const QList<Scan> &scans);
    static QList<Scan> splitByAxisX(const Scan &s, double precision);
    static QList<Scan> snakeSplit(const Scan &s);

};

#endif // LINEARSCANINTERACTOR_H
