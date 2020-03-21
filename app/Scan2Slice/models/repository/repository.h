#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "models/settings_manager/settings_manager.h"

#include "models/types/point_3d/point_3d.h"
#include "models/types/scan/scan.h"

class Router;

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

    QList<Scan> scans() const;
    void setScans(const QList<Scan> &scans);

    QList<Point3D> points() const;

private:
    QString m_gCodesViewer;
    QList<Scan> m_scans;

    friend class Router;

signals:

public slots:
};

#endif // REPOSITORY_H
