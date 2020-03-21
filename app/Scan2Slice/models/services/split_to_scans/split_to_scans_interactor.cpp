#include "split_to_scans_interactor.h"

SplitToScansInteractor::SplitToScansInteractor()
{

}

QList<Scan> SplitToScansInteractor::execute(QList<Point3D> points, double toleranceX)
{
    qDebug() << toleranceX;
    if(points.length() <= 0) return {};
    if(points.length() == 1) return { Scan(points) };

    QList<Scan> result = { Scan({ points[0] }) };

    for(int i = 1; i < points.length(); i++)
    {
        if((points[i].x() - points[i-1].x()) > toleranceX)
        {
            result.append(Scan({ points[i] }));
        }
        else
        {
            result.last().append(points[i]);
        }
    }

    return result;
}
