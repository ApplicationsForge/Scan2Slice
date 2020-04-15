#ifndef LINEARSCANINTERACTOR_H
#define LINEARSCANINTERACTOR_H

#include <QDebug>

#include "models/router.h"

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
    static void snakeExecute(double distanceFromLaser, double step, double generalRotationAngle);
private:
    /**
     * @brief Запускает сценарий без модификации исходных данных
     * @param scans - исходные сканы
     * @param distanceFromLaser - расстояние от лазера до оси вращения
     * @param step - дискретность угла поворота в градусах
     * @param generalRotationAngle - угол на который нужно повернуть все точки
     * @return преобразованные сканы
     */
    static QList<Scan> transform(const QList<Scan> &scans, double distanceFromLaser, double step, double generalRotationAngle);
};

#endif // LINEARSCANINTERACTOR_H
