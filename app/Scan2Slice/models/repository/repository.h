#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "models/settings_manager/settings_manager.h"

#include "models/types/point_3d/point_3d.h"

class Router;

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

    QString helloString() const;
    void setHelloString(const QString &helloString);

    QList<Point3D> points() const;
    void setPoints(const QList<Point3D> &points);

private:
    QString m_helloString = "Hello World!";
    QString m_gCodesViewer;
    QList<Point3D> m_points;

    friend class Router;

signals:

public slots:
};

#endif // REPOSITORY_H
